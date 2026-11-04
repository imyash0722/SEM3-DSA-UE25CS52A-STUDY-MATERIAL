#!/usr/bin/env python3
"""
Pipeline for converting documents to PDF, running OCR, and extracting all text.
"""
import os
import sys
import glob
import subprocess
import shutil
import fitz
from pathlib import Path

BASE_DIR = Path("/mnt/shared/sem3/DSA").resolve()

def run_cmd(cmd, check=True):
    # Run command and return output
    p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if check and p.returncode != 0:
        print(f"Error executing {' '.join(cmd)}:\n{p.stderr}")
    return p

def convert_to_pdf(input_path: Path, output_dir: Path):
    cmd = ["libreoffice", "--headless", "--convert-to", "pdf", str(input_path), "--outdir", str(output_dir)]
    run_cmd(cmd, check=True)
    pdf_name = input_path.stem + ".pdf"
    out_pdf = output_dir / pdf_name
    return out_pdf

def ocr_pdf(pdf_path: Path):
    """
    Run ocrmypdf with --skip-text to preserve vector text and add OCR to image pages.
    """
    temp_out = pdf_path.with_suffix(".tmp_ocr.pdf")
    cmd = [
        "uvx", "ocrmypdf",
        "--skip-text",
        "--output-type", "pdf",
        str(pdf_path),
        str(temp_out)
    ]
    p = run_cmd(cmd, check=False)
    if p.returncode == 0 and temp_out.exists() and temp_out.stat().st_size > 0:
        shutil.move(temp_out, pdf_path)
        return True
    else:
        if temp_out.exists():
            temp_out.unlink()
        print(f"Warning: OCRmyPDF on {pdf_path.name} failed or skipped: {p.stderr[:200]}")
        return False

def extract_text_from_pdf(pdf_path: Path, txt_path: Path):
    """
    Extract all text from PDF using PyMuPDF and embedded image OCR for diagrams.
    """
    doc = fitz.open(pdf_path)
    extracted_pages = []
    
    for page_idx, page in enumerate(doc):
        page_num = page_idx + 1
        page_text = page.get_text("text").strip()
        
        # Check if page has embedded images that might have diagram text
        imgs = page.get_images(full=True)
        img_texts = []
        for img_info in imgs:
            xref = img_info[0]
            try:
                base_img = doc.extract_image(xref)
                w, h = base_img["width"], base_img["height"]
                # Skip tiny icons or logo banners (like standard header 232x119)
                if w < 100 or h < 50:
                    continue
                # If the page already had plenty of text, avoid re-OCRing headers/logos
                # Only OCR diagram images
                if (w, h) in [(232, 119), (293, 150)]:
                    continue
                
                img_bytes = base_img["image"]
                tess = subprocess.run(
                    ["tesseract", "stdin", "stdout", "--psm", "6"],
                    input=img_bytes,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE
                )
                t_out = tess.stdout.decode("utf-8", errors="replace").strip()
                if len(t_out) > 10 and t_out not in page_text:
                    img_texts.append(t_out)
            except Exception:
                pass
        
        combined_page = [f"--- Page {page_num} ---"]
        if page_text:
            combined_page.append(page_text)
        if img_texts:
            combined_page.append("[Diagram / Image OCR Content]:")
            combined_page.extend(img_texts)
            
        extracted_pages.append("\n\n".join(combined_page))
        
    full_text = "\n\n" + ("\n\n" + "="*40 + "\n\n").join(extracted_pages) + "\n"
    txt_path.write_text(full_text, encoding="utf-8")
    return full_text

if __name__ == "__main__":
    print("Script template ready.")
