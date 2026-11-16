#!/usr/bin/env python3
"""
Merge all extracted text, notes, slides, MCQs, and assignments into
one big file per unit.
Outputs:
- UNIT_1_ALL_CONTENT.txt
- UNIT_2_ALL_CONTENT.txt
- UNIT_3_ALL_CONTENT.txt
Both in root and in resources/extracted_text/
"""

import os
import re
from pathlib import Path

ROOT = Path("/mnt/shared/sem3/DSA").resolve()
RESOURCES = ROOT / "resources"
DATA_DIR = RESOURCES / "Data_Structures_and_its_Applications"
OUT_DIR = RESOURCES / "extracted_text"

def natural_key(string_):
    return [int(s) if s.isdigit() else s.lower() for s in re.split(r'(\d+)', str(string_))]

def read_file_safe(p: Path):
    if not p.exists():
        return ""
    try:
        return p.read_text(encoding="utf-8", errors="replace")
    except Exception as e:
        print(f"Error reading {p}: {e}")
        return ""

def build_unit_file(unit_num: int):
    print(f"Building big file for Unit {unit_num}...")
    content_parts = []
    
    header = f"""{"#" * 80}
# DATA STRUCTURES AND APPLICATIONS (UE25CS52A)
# COMPLETE AGGREGATED CONTENT - UNIT {unit_num}
# Contains: All Lecture Notes, All Slides, Assignments & MCQs (with OCR)
{"#" * 80}
"""
    content_parts.append(header)
    
    unit_dir = DATA_DIR / str(unit_num)
    notes_dir = unit_dir / "Notes"
    slides_dir = unit_dir / "Slides"
    assignments_dir = unit_dir / "Assignments"
    
    # 1. Notes
    content_parts.append(f"\n\n{'=' * 80}\nSECTION 1: LECTURE NOTES (UNIT {unit_num})\n{'=' * 80}\n")
    if notes_dir.exists():
        note_txts = sorted(notes_dir.glob("*.txt"), key=natural_key)
        for n_txt in note_txts:
            title = n_txt.stem
            text = read_file_safe(n_txt).strip()
            content_parts.append(f"\n\n{'-' * 60}\n[NOTE DOCUMENT]: {title}\nFile: {n_txt.name}\n{'-' * 60}\n\n{text}\n")
    
    # 2. Slides
    content_parts.append(f"\n\n{'=' * 80}\nSECTION 2: LECTURE SLIDES (UNIT {unit_num})\n{'=' * 80}\n")
    if slides_dir.exists():
        slide_txts = sorted(slides_dir.glob("*.txt"), key=natural_key)
        for s_txt in slide_txts:
            title = s_txt.stem
            text = read_file_safe(s_txt).strip()
            content_parts.append(f"\n\n{'-' * 60}\n[SLIDE PRESENTATION]: {title}\nFile: {s_txt.name}\n{'-' * 60}\n\n{text}\n")
            
    # 3. MCQs (if present for this unit)
    mcq_file = RESOURCES / f"DSA_Unit_{unit_num}_MCQs_Questions_Only_Answers_at_End.txt"
    if not mcq_file.exists():
        # Check extracted_text
        alt_mcq = OUT_DIR / f"unit{unit_num}_mcqs.txt"
        if alt_mcq.exists():
            mcq_file = alt_mcq
    if mcq_file.exists():
        mcq_text = read_file_safe(mcq_file).strip()
        content_parts.append(f"\n\n{'=' * 80}\nSECTION 3: MCQS & QUESTION BANK (UNIT {unit_num})\n{'=' * 80}\n\n{mcq_text}\n")
        
    # 4. Assignments
    if assignments_dir.exists():
        content_parts.append(f"\n\n{'=' * 80}\nSECTION 4: ASSIGNMENTS & HOMEWORK (UNIT {unit_num})\n{'=' * 80}\n")
        assign_txts = sorted(assignments_dir.glob("*.txt"), key=natural_key)
        for a_txt in assign_txts:
            title = a_txt.name
            text = read_file_safe(a_txt).strip()
            content_parts.append(f"\n\n{'-' * 60}\n[ASSIGNMENT]: {title}\n{'-' * 60}\n\n{text}\n")

    full_unit_text = "\n".join(content_parts)
    
    # Write to resources/extracted_text/
    out_file1 = OUT_DIR / f"UNIT_{unit_num}_ALL_CONTENT.txt"
    out_file1.write_text(full_unit_text, encoding="utf-8")
    
    # Also write to root for easy access
    out_file2 = ROOT / f"UNIT_{unit_num}_ALL_CONTENT.txt"
    out_file2.write_text(full_unit_text, encoding="utf-8")
    
    print(f"Unit {unit_num} Big File Created:")
    print(f"  Path: {out_file2}")
    print(f"  Size: {len(full_unit_text):,} characters, {len(full_unit_text.splitlines()):,} lines")
    return out_file2

def main():
    print("=== Aggregating all content into big files per unit ===")
    units = [1, 2, 3]
    for u in units:
        build_unit_file(u)
    print("\nAll unit big files created successfully!")

if __name__ == "__main__":
    main()
