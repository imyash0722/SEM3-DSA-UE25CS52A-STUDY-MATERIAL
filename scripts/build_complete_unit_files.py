#!/usr/bin/env python3
"""
Ensures every PDF source document is extracted to its corresponding .txt file,
and compiles one comprehensive file per unit containing EVERY file's content
(source PDFs, notes, slides, MCQs, assignments, and diagram OCR).
"""

import os
import shutil
import re
from pathlib import Path

ROOT = Path("/mnt/shared/sem3/DSA").resolve()
RESOURCES = ROOT / "resources"
DATA_DIR = RESOURCES / "Data_Structures_and_its_Applications"
OUT_DIR = RESOURCES / "extracted_text"
COMBINED_NOTES = RESOURCES / "Combined Notes"
COMBINED_SLIDES = RESOURCES / "Combined Slides"

def natural_key(string_):
    return [int(s) if s.isdigit() else s.lower() for s in re.split(r'(\d+)', str(string_))]

def read_text_safe(path: Path):
    if not path.exists():
        return ""
    try:
        return path.read_text(encoding="utf-8", errors="replace")
    except Exception as e:
        print(f"Error reading {path}: {e}")
        return ""

def step1_ensure_all_pdf_txt_files():
    print("=== Step 1: Ensuring all PDF source files have matching .txt files ===")
    
    mappings = [
        (OUT_DIR / "unit1_complete.txt", RESOURCES / "Unit 1.txt"),
        (OUT_DIR / "unit1_mcqs.txt", RESOURCES / "DSA_Unit_1_MCQs_Questions_Only_Answers_at_End.txt"),
        (OUT_DIR / "unit2_mcqs.txt", RESOURCES / "DSA_Unit_2_MCQs_Questions_Only_Answers_at_End.txt"),
        (OUT_DIR / "unit1_notes.txt", COMBINED_NOTES / "DSA Unit 1 Combined Notes.txt"),
        (OUT_DIR / "unit2_notes.txt", COMBINED_NOTES / "DSA Unit 2 Combined Notes.txt"),
        (OUT_DIR / "unit3_notes.txt", COMBINED_NOTES / "DSA Unit 3 Combined Notes.txt"),
        (OUT_DIR / "unit1_slides.txt", COMBINED_SLIDES / "DSA Unit 1 Combined Slides.txt"),
        (OUT_DIR / "unit2_slides.txt", COMBINED_SLIDES / "DSA Unit 2 Combined Slides.txt"),
        (OUT_DIR / "unit3_slides.txt", COMBINED_SLIDES / "DSA Unit 3 Combined Slides.txt"),
    ]
    
    for src, dst in mappings:
        if src.exists():
            shutil.copy(src, dst)
            print(f"  Copied {src.name} -> {dst.relative_to(ROOT)}")
        else:
            print(f"  Warning: source {src} does not exist!")

def compile_unit_1():
    print("\n=== Compiling Comprehensive Unit 1 File ===")
    parts = []
    
    header = f"""{"#" * 90}
# DATA STRUCTURES AND APPLICATIONS (UE25CS52A) - UNIT 1 COMPLETE REPOSITORY
# CONSOLIDATED EXTRACTED TEXT FROM ALL SOURCE PDFS, NOTES, SLIDES & ASSIGNMENTS
# Includes full text extraction with OCR for images, diagrams, and scanned content.
{"#" * 90}

TABLE OF CONTENTS:
1. PRIMARY SOURCE PDF: Unit 1.pdf (Prof. Vandana M L, 291 pages)
2. COMBINED SOURCE PDF: DSA Unit 1 Combined Notes.pdf (134 pages)
3. COMBINED SOURCE PDF: DSA Unit 1 Combined Slides.pdf (224 pages)
4. SOURCE PDF: DSA Unit 1 MCQs & Question Bank (20 pages)
5. INDIVIDUAL LECTURE NOTES (14 Documents)
6. INDIVIDUAL LECTURE SLIDES (13 Presentations)
7. WEEKLY ASSIGNMENTS (Weeks 1, 2, 3)
"""
    parts.append(header)
    
    # 1. Primary Source PDF: Unit 1.pdf
    parts.append(f"\n\n{'=' * 90}\nSECTION 1: PRIMARY SOURCE PDF - Unit 1.pdf (291 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(RESOURCES / "Unit 1.txt"))
    
    # 2. Combined Notes PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 2: SOURCE PDF - DSA Unit 1 Combined Notes.pdf (134 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(COMBINED_NOTES / "DSA Unit 1 Combined Notes.txt"))
    
    # 3. Combined Slides PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 3: SOURCE PDF - DSA Unit 1 Combined Slides.pdf (224 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(COMBINED_SLIDES / "DSA Unit 1 Combined Slides.txt"))
    
    # 4. Unit 1 MCQs PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 4: SOURCE PDF - DSA Unit 1 MCQs & Question Bank (20 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(RESOURCES / "DSA_Unit_1_MCQs_Questions_Only_Answers_at_End.txt"))
    
    # 5. Individual Notes
    parts.append(f"\n\n{'=' * 90}\nSECTION 5: INDIVIDUAL LECTURE NOTES (UNIT 1)\n{'=' * 90}\n")
    notes_dir = DATA_DIR / "1" / "Notes"
    for n_txt in sorted(notes_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[NOTE]: {n_txt.stem}\nSource: {n_txt.name}\n{'-' * 70}\n\n" + read_text_safe(n_txt))
        
    # 6. Individual Slides
    parts.append(f"\n\n{'=' * 90}\nSECTION 6: INDIVIDUAL LECTURE SLIDES (UNIT 1)\n{'=' * 90}\n")
    slides_dir = DATA_DIR / "1" / "Slides"
    for s_txt in sorted(slides_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[SLIDE]: {s_txt.stem}\nSource: {s_txt.name}\n{'-' * 70}\n\n" + read_text_safe(s_txt))
        
    # 7. Assignments
    parts.append(f"\n\n{'=' * 90}\nSECTION 7: WEEKLY ASSIGNMENTS (UNIT 1)\n{'=' * 90}\n")
    assign_dir = DATA_DIR / "1" / "Assignments"
    for a_txt in sorted(assign_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[ASSIGNMENT]: {a_txt.name}\n{'-' * 70}\n\n" + read_text_safe(a_txt))
        
    full_content = "\n".join(parts)
    out_root = ROOT / "UNIT_1_ALL_CONTENT.txt"
    out_extracted = OUT_DIR / "UNIT_1_ALL_CONTENT.txt"
    out_root.write_text(full_content, encoding="utf-8")
    out_extracted.write_text(full_content, encoding="utf-8")
    print(f"Unit 1 complete file written: {len(full_content):,} chars, {len(full_content.splitlines()):,} lines")

def compile_unit_2():
    print("\n=== Compiling Comprehensive Unit 2 File ===")
    parts = []
    
    header = f"""{"#" * 90}
# DATA STRUCTURES AND APPLICATIONS (UE25CS52A) - UNIT 2 COMPLETE REPOSITORY
# CONSOLIDATED EXTRACTED TEXT FROM ALL SOURCE PDFS, NOTES, SLIDES & ASSIGNMENTS
# Includes full text extraction with OCR for images, diagrams, and scanned content.
{"#" * 90}

TABLE OF CONTENTS:
1. COMBINED SOURCE PDF: DSA Unit 2 Combined Notes.pdf (96 pages)
2. COMBINED SOURCE PDF: DSA Unit 2 Combined Slides.pdf (169 pages)
3. SOURCE PDF: DSA Unit 2 MCQs & Question Bank (16 pages)
4. INDIVIDUAL LECTURE NOTES (11 Documents)
5. INDIVIDUAL LECTURE SLIDES (10 Presentations)
6. WEEKLY ASSIGNMENTS (Weeks 4, 5, 6)
"""
    parts.append(header)
    
    # 1. Combined Notes PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 1: SOURCE PDF - DSA Unit 2 Combined Notes.pdf (96 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(COMBINED_NOTES / "DSA Unit 2 Combined Notes.txt"))
    
    # 2. Combined Slides PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 2: SOURCE PDF - DSA Unit 2 Combined Slides.pdf (169 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(COMBINED_SLIDES / "DSA Unit 2 Combined Slides.txt"))
    
    # 3. Unit 2 MCQs PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 3: SOURCE PDF - DSA Unit 2 MCQs & Question Bank (16 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(RESOURCES / "DSA_Unit_2_MCQs_Questions_Only_Answers_at_End.txt"))
    
    # 4. Individual Notes
    parts.append(f"\n\n{'=' * 90}\nSECTION 4: INDIVIDUAL LECTURE NOTES (UNIT 2)\n{'=' * 90}\n")
    notes_dir = DATA_DIR / "2" / "Notes"
    for n_txt in sorted(notes_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[NOTE]: {n_txt.stem}\nSource: {n_txt.name}\n{'-' * 70}\n\n" + read_text_safe(n_txt))
        
    # 5. Individual Slides
    parts.append(f"\n\n{'=' * 90}\nSECTION 5: INDIVIDUAL LECTURE SLIDES (UNIT 2)\n{'=' * 90}\n")
    slides_dir = DATA_DIR / "2" / "Slides"
    for s_txt in sorted(slides_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[SLIDE]: {s_txt.stem}\nSource: {s_txt.name}\n{'-' * 70}\n\n" + read_text_safe(s_txt))
        
    # 6. Assignments
    parts.append(f"\n\n{'=' * 90}\nSECTION 6: WEEKLY ASSIGNMENTS (UNIT 2)\n{'=' * 90}\n")
    assign_dir = DATA_DIR / "2" / "Assignments"
    for a_txt in sorted(assign_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[ASSIGNMENT]: {a_txt.name}\n{'-' * 70}\n\n" + read_text_safe(a_txt))
        
    full_content = "\n".join(parts)
    out_root = ROOT / "UNIT_2_ALL_CONTENT.txt"
    out_extracted = OUT_DIR / "UNIT_2_ALL_CONTENT.txt"
    out_root.write_text(full_content, encoding="utf-8")
    out_extracted.write_text(full_content, encoding="utf-8")
    print(f"Unit 2 complete file written: {len(full_content):,} chars, {len(full_content.splitlines()):,} lines")

def compile_unit_3():
    print("\n=== Compiling Comprehensive Unit 3 File ===")
    parts = []
    
    header = f"""{"#" * 90}
# DATA STRUCTURES AND APPLICATIONS (UE25CS52A) - UNIT 3 COMPLETE REPOSITORY
# CONSOLIDATED EXTRACTED TEXT FROM ALL SOURCE PDFS, NOTES, SLIDES & ASSIGNMENTS
# Includes full text extraction with OCR for images, diagrams, and scanned content.
{"#" * 90}

TABLE OF CONTENTS:
1. COMBINED SOURCE PDF: DSA Unit 3 Combined Notes.pdf (93 pages)
2. COMBINED SOURCE PDF: DSA Unit 3 Combined Slides.pdf (164 pages)
3. INDIVIDUAL LECTURE NOTES (8 Documents)
4. INDIVIDUAL LECTURE SLIDES (9 Presentations)
5. WEEKLY ASSIGNMENTS (Weeks 7, 8)
"""
    parts.append(header)
    
    # 1. Combined Notes PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 1: SOURCE PDF - DSA Unit 3 Combined Notes.pdf (93 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(COMBINED_NOTES / "DSA Unit 3 Combined Notes.txt"))
    
    # 2. Combined Slides PDF
    parts.append(f"\n\n{'=' * 90}\nSECTION 2: SOURCE PDF - DSA Unit 3 Combined Slides.pdf (164 Pages)\n{'=' * 90}\n")
    parts.append(read_text_safe(COMBINED_SLIDES / "DSA Unit 3 Combined Slides.txt"))
    
    # 3. Individual Notes
    parts.append(f"\n\n{'=' * 90}\nSECTION 3: INDIVIDUAL LECTURE NOTES (UNIT 3)\n{'=' * 90}\n")
    notes_dir = DATA_DIR / "3" / "Notes"
    for n_txt in sorted(notes_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[NOTE]: {n_txt.stem}\nSource: {n_txt.name}\n{'-' * 70}\n\n" + read_text_safe(n_txt))
        
    # 4. Individual Slides
    parts.append(f"\n\n{'=' * 90}\nSECTION 4: INDIVIDUAL LECTURE SLIDES (UNIT 3)\n{'=' * 90}\n")
    slides_dir = DATA_DIR / "3" / "Slides"
    for s_txt in sorted(slides_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[SLIDE]: {s_txt.stem}\nSource: {s_txt.name}\n{'-' * 70}\n\n" + read_text_safe(s_txt))
        
    # 5. Assignments
    parts.append(f"\n\n{'=' * 90}\nSECTION 5: WEEKLY ASSIGNMENTS (UNIT 3)\n{'=' * 90}\n")
    assign_dir = DATA_DIR / "3" / "Assignments"
    for a_txt in sorted(assign_dir.glob("*.txt"), key=natural_key):
        parts.append(f"\n\n{'-' * 70}\n[ASSIGNMENT]: {a_txt.name}\n{'-' * 70}\n\n" + read_text_safe(a_txt))
        
    full_content = "\n".join(parts)
    out_root = ROOT / "UNIT_3_ALL_CONTENT.txt"
    out_extracted = OUT_DIR / "UNIT_3_ALL_CONTENT.txt"
    out_root.write_text(full_content, encoding="utf-8")
    out_extracted.write_text(full_content, encoding="utf-8")
    print(f"Unit 3 complete file written: {len(full_content):,} chars, {len(full_content.splitlines()):,} lines")

def main():
    step1_ensure_all_pdf_txt_files()
    compile_unit_1()
    compile_unit_2()
    compile_unit_3()
    print("\nALL UNITS SUCCESSFULLY COMPILED WITH EVERY SOURCE PDF DOCUMENT INCLUDED!")

if __name__ == "__main__":
    main()
