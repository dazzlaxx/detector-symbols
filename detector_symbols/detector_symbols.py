#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import argparse

all_issues = []

def detect_incorrect_encoding(filepath):
    issues_found = []
    
    try:
        with open(filepath, 'rb') as f:
            content = f.read()
        
        try:
            utf8_content = content.decode('utf-8')
            if 'ï' in utf8_content or 'Â' in utf8_content or 'Ã' in utf8_content:
                issues_found.append({
                    'line': 0,
                    'issue': 'Возможное двойное кодирование UTF-8 → CP1251 → UTF-8',
                    'content': 'Обнаружены характерные символы двойного кодирования'
                })
                
        except UnicodeDecodeError:
            try:
                cp1251_content = content.decode('cp1251')

                problematic_chars = []
                for i, char in enumerate(cp1251_content):
                    if ord(char) > 127:  
                        problematic_chars.append((i, char, ord(char)))
                
                if problematic_chars:
                    issues_found.append({
                        'line': 0,
                        'issue': 'Обнаружены не-ASCII символы в CP1251',
                        'content': f'Проблемные символы: {problematic_chars[:5]}'  
                    })
                    
            except UnicodeDecodeError:
                issues_found.append({
                    'line': 0,
                    'issue': 'Неизвестная кодировка файла',
                    'content': 'Файл не может быть декодирован как UTF-8 или CP1251'
                })
        
        with open(filepath, 'rb') as f:
            lines = f.readlines()
            
        for line_num, line_bytes in enumerate(lines, start=1):
            try:
                line_cp1251 = line_bytes.decode('cp1251')
                
                if any(c in line_cp1251 for c in ['ï', 'Â', 'Ã', '©', '®', '²', '³']):
                    issues_found.append({
                        'line': line_num,
                        'issue': 'Возможное двойное кодирование в строке',
                        'content': repr(line_cp1251[:100])  
                    })
                    
            except UnicodeDecodeError:
                try:
                    line_utf8 = line_bytes.decode('utf-8')
                    issues_found.append({
                        'line': line_num,
                        'issue': 'Строка в UTF-8 в файле CP1251',
                        'content': repr(line_utf8[:100])
                    })
                except UnicodeDecodeError:
                    issues_found.append({
                        'line': line_num,
                        'issue': 'Не удается декодировать строку',
                        'content': repr(line_bytes[:50])  
                    })
                    
    except Exception as e:
        issues_found.append({
            'line': 0,
            'issue': f'Ошибка чтения файла: {e}',
            'content': ''
        })
    
    return issues_found

def should_skip_file(filename):
    if filename.endswith(('.py', '.pyc', '.pyo')):
        return True
    
    if filename.endswith(('.pyproj', '.sln', '.csproj', '.vbproj', '.vcxproj')):
        return True
    
    if filename.endswith(('.suo', '.user', '.ide', '.vs', '.vscode')):
        return True
    
    if filename.endswith(('.exe', '.dll', '.so', '.bin', '.dat', '.pdb', '.obj', '.lib')):
        return True
    
    if filename.endswith(('.zip', '.rar', '.7z', '.tar', '.gz', '.bz2')):
        return True
    
    if filename.endswith(('.jpg', '.jpeg', '.png', '.gif', '.bmp', '.mp3', '.mp4', '.avi', '.mkv')):
        return True
    
    if filename.startswith(('.', '__')):
        return True
    
    if filename in ('package.json', 'package-lock.json', 'requirements.txt', 'Pipfile', 'Pipfile.lock'):
        return True
    
    return False

def analyze_file(filepath, relative_to=None):
    """Анализирует один файл и возвращает результаты"""
    global all_issues
    
    if relative_to:
        display_path = os.path.relpath(filepath, relative_to)
    else:
        display_path = os.path.basename(filepath)
    
    if should_skip_file(os.path.basename(filepath)):
        return False
    
    issues = detect_incorrect_encoding(filepath)
    
    if issues:
        print(f"\n{'='*80}")
        print(f"Файл: {display_path}")
        print(f"{'='*80}")
        
        for issue in issues:
            if issue['line'] > 0:
                print(f"Строка {issue['line']}: {issue['issue']}")
                print(f"Содержимое: {issue['content']}")
            else:
                print(f"{issue['issue']}")
                print(f"Детали: {issue['content']}")
            
            all_issues.append({
                'file': display_path,
                'line': issue['line'],
                'issue': issue['issue'],
                'content': issue['content']
            })
        
        return True
    return False

def analyze_directory(directory_path):
    """Рекурсивно анализирует все файлы в директории"""
    issues_count = 0
    directory_path = os.path.abspath(directory_path)
    
    print(f"Анализ директории: {os.path.basename(directory_path)}")
    print(f"Пропускаем: Python файлы, проекты, бинарные файлы, медиафайлы")
    print(f"{'='*80}")
    
    for root, dirs, files in os.walk(directory_path):
        for file in files:
            filepath = os.path.join(root, file)
            try:
                if analyze_file(filepath, directory_path):
                    issues_count += 1
            except Exception as e:
                print(f"Ошибка при анализе файла {filepath}: {e}")
    
    return issues_count

def print_summary():
    """Выводит итоговый отчет со всеми найденными ошибками"""
    if not all_issues:
        print("\n" + "="*80)
        print("ОШИБОК КОДИРОВКИ НЕ НАЙДЕНО!")
        print("="*80)
        return
    
    print("\n" + "="*80)
    print("ИТОГОВЫЙ ОТЧЕТ ОБ ОШИБКАХ КОДИРОВКИ")
    print("="*80)
    
    files_with_issues = {}
    for issue in all_issues:
        if issue['file'] not in files_with_issues:
            files_with_issues[issue['file']] = []
        files_with_issues[issue['file']].append(issue)
    
    for file_path, issues in files_with_issues.items():
        print(f"\nФАЙЛ: {file_path}")
        print("-" * 60)
        
        for issue in issues:
            if issue['line'] > 0:
                print(f"  Строка {issue['line']:4d}: {issue['issue']}")
                if len(issue['content']) > 100:
                    print(f"         Содержимое: {issue['content'][:100]}...")
                else:
                    print(f"         Содержимое: {issue['content']}")
            else:
                print(f"  {issue['issue']}")
                if issue['content']:
                    print(f"         Детали: {issue['content']}")
    
    print("\n" + "="*80)
    print("СВОДНАЯ СТАТИСТИКА:")
    print("="*80)
    print(f"Всего файлов с ошибками: {len(files_with_issues)}")
    print(f"Всего ошибок: {len(all_issues)}")
    
    error_types = {}
    for issue in all_issues:
        error_type = issue['issue']
        error_types[error_type] = error_types.get(error_type, 0) + 1
    
    print("\nТипы ошибок:")
    for error_type, count in error_types.items():
        print(f"  {error_type}: {count}")

def main():
    global all_issues
    all_issues = []  
    
    parser = argparse.ArgumentParser(
        description='Детектор проблем с кодировкой (UTF-8/CP1251)',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
Примеры использования:
  python detector_symbols.py umerror.h    # Анализ конкретного файла
  python detector_symbols.py .            # Анализ текущей директории
  python detector_symbols.py              # Анализ текущей директории
        '''
    )
    
    parser.add_argument(
        'path',
        nargs='?',
        default='.',
        help='Путь к файлу или директории для анализа'
    )
    
    args = parser.parse_args()
    
    if not os.path.exists(args.path):
        print(f"Ошибка: путь '{args.path}' не существует")
        sys.exit(1)
    
    if os.path.isfile(args.path):
        print("Анализ файла...")
        if not should_skip_file(os.path.basename(args.path)):
            analyze_file(args.path)
        else:
            print(f"Файл {args.path} пропущен (не текстовый файл)")
    elif os.path.isdir(args.path):
        issues_count = analyze_directory(args.path)
        print(f"\n{'='*80}")
        print(f"Анализ завершен. Найдено файлов с проблемами: {issues_count}")
    else:
        print("Ошибка: указанный путь не является файлом или директорией")
        sys.exit(1)
    
    print_summary()

if __name__ == "__main__":
    main()