#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import argparse

all_issues = []

def detect_incorrect_encoding(filepath):
    issues_found = []
    
    try:
        # Читаем файл как бинарный
        with open(filepath, 'rb') as f:
            lines = f.readlines()
            
        # Анализируем каждую строку
        for line_num, line_bytes in enumerate(lines, start=1):
            if not line_bytes.strip():  # Пропускаем пустые строки
                continue
                
            # Пробуем декодировать строку разными кодировками
            decoded_lines = {}
            
            for encoding in ['utf-8', 'cp1251', 'iso-8859-1', 'cp866']:
                try:
                    decoded_text = line_bytes.decode(encoding)
                    decoded_lines[encoding] = decoded_text
                except UnicodeDecodeError:
                    continue
            
            # Если не удалось декодировать ни одной кодировкой
            if not decoded_lines:
                issues_found.append({
                    'line': line_num,
                    'issue': 'Не удается декодировать строку',
                    'content': f'Бинарные данные: {line_bytes[:50].hex()}'
                })
                continue
            
            # Проверяем каждую декодированную версию на ошибки
            for encoding, line_text in decoded_lines.items():
                # Ищем характерные признаки двойного кодирования
                problematic_chars = []
                
                for i, char in enumerate(line_text):
                    code = ord(char)
                    # Символы, которые часто появляются при двойном кодировании
                    if code == 0xEF:  # ï
                        problematic_chars.append((i, 'ï', '0xEF'))
                    elif code == 0xC2:  # Â
                        problematic_chars.append((i, 'Â', '0xC2'))
                    elif code == 0xC3:  # Ã
                        problematic_chars.append((i, 'Ã', '0xC3'))
                    elif code == 0xA9:  # ©
                        problematic_chars.append((i, '©', '0xA9'))
                    elif code == 0xAE:  # ®
                        problematic_chars.append((i, '®', '0xAE'))
                    elif code == 0xB2:  # ²
                        problematic_chars.append((i, '²', '0xB2'))
                    elif code == 0xB3:  # ³
                        problematic_chars.append((i, '³', '0xB3'))
                    elif code == 0xB0:  # °
                        problematic_chars.append((i, '°', '0xB0'))
                    elif code == 0xB1:  # ±
                        problematic_chars.append((i, '±', '0xB1'))
                    elif code == 0xB5:  # µ
                        problematic_chars.append((i, 'µ', '0xB5'))
                    # Любые другие не-ASCII символы в предположительно ASCII тексте
                    elif code > 127 and not line_text.strip().startswith(('//', '/*', '*')):
                        problematic_chars.append((i, char, f'0x{code:02X}'))
                
                if problematic_chars:
                    # Берем только первые 5 проблемных символов для вывода
                    short_list = problematic_chars[:5]
                    issues_found.append({
                        'line': line_num,
                        'issue': f'Проблемные символы в кодировке {encoding}',
                        'content': f'Символы: {short_list} | Текст: {repr(line_text.strip()[:100])}'
                    })
                    
    except Exception as e:
        issues_found.append({
            'line': 0,
            'issue': f'Ошибка чтения файла: {e}',
            'content': ''
        })
    
    return issues_found

def should_analyze_file(filepath):
    """Определяет, нужно ли анализировать файл"""
    filename = os.path.basename(filepath)
    _, ext = os.path.splitext(filename.lower())
    
    # Пропускаем Python файлы
    if ext == '.py':
        return False
    
    # Пропускаем явно бинарные файлы
    binary_extensions = [
        '.exe', '.dll', '.so', '.bin', '.dat', '.pdb', '.obj', '.lib',
        '.zip', '.rar', '.7z', '.tar', '.gz', '.bz2', '.jpg', '.jpeg', 
        '.png', '.gif', '.bmp', '.mp3', '.mp4', '.avi', '.mkv', '.pdf',
        '.doc', '.docx', '.xls', '.xlsx', '.ppt', '.pptx'
    ]
    
    if ext in binary_extensions:
        return False
    
    # Пропускаем системные файлы
    if filename in ['Thumbs.db', '.DS_Store', 'desktop.ini']:
        return False
    
    # Пропускаем скрытые файлы
    if filename.startswith('.'):
        return False
    
    # Для файлов без расширения проверяем, текстовые ли они
    if ext == '':
        try:
            with open(filepath, 'rb') as f:
                sample = f.read(1024)
                # Если в первых 1024 байтах есть нулевые байты - вероятно бинарный файл
                if b'\x00' in sample:
                    return False
        except:
            return False
    
    # Анализируем все остальные файлы
    return True

def analyze_file(filepath, show_full_path=True):
    """Анализирует один файл и возвращает результаты"""
    global all_issues
    
    # Всегда используем полный абсолютный путь
    full_path = os.path.abspath(filepath)
    display_path = full_path  # Всегда показываем полный путь
    
    # Проверяем, нужно ли анализировать этот файл
    if not should_analyze_file(filepath):
        return False
    
    print(f"Анализируем: {display_path}")
    
    issues = detect_incorrect_encoding(filepath)
    
    if issues:
        print(f"  Найдено проблем: {len(issues)}")
        
        # ВЫВОДИМ РЕЗУЛЬТАТЫ СРАЗУ ЖЕ С ПОЛНЫМ ПУТЕМ К ФАЙЛУ
        print(f"\n{'='*100}")
        print(f"ФАЙЛ: {display_path}")
        print(f"{'='*100}")
        
        for issue in issues:
            if issue['line'] > 0:
                print(f"Строка {issue['line']}: {issue['issue']}")
                print(f"Содержимое: {issue['content']}")
            else:
                print(f"{issue['issue']}")
                if issue['content']:
                    print(f"Детали: {issue['content']}")
            print("-" * 60)
        
        # Сохраняем все проблемы с полным путем
        for issue in issues:
            all_issues.append({
                'file': display_path,  # Сохраняем ПОЛНЫЙ абсолютный путь
                'line': issue['line'],
                'issue': issue['issue'],
                'content': issue['content']
            })
        
        return True
    else:
        print(f"  Проблем не найдено")
        return False

def analyze_directory(directory_path):
    """Рекурсивно анализирует все файлы в директории"""
    issues_count = 0
    directory_path = os.path.abspath(directory_path)
    
    print(f"Анализ директории: {directory_path}")
    print(f"Проверяем все файлы, кроме Python и бинарных")
    print(f"{'='*100}")
    
    total_files = 0
    analyzed_files = 0
    
    for root, dirs, files in os.walk(directory_path):
        # Пропускаем скрытые директории
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        
        for file in files:
            total_files += 1
            filepath = os.path.join(root, file)
            
            try:
                # Всегда передаем полный путь и показываем полный путь
                if analyze_file(filepath, show_full_path=True):
                    issues_count += 1
                analyzed_files += 1
            except Exception as e:
                print(f"Ошибка при анализе файла {filepath}: {e}")
    
    print(f"\nПроанализировано файлов: {analyzed_files}")
    return issues_count

def print_summary():
    """Выводит итоговый отчет со всеми найденными ошибками"""
    if not all_issues:
        print("\n" + "="*100)
        print("ОШИБОК КОДИРОВКИ НЕ НАЙДЕНО!")
        print("="*100)
        return
    
    print("\n" + "="*100)
    print("ИТОГОВЫЙ ОТЧЕТ ОБ ОШИБКАХ КОДИРОВКИ")
    print("="*100)
    
    # Группируем по файлам
    files_with_issues = {}
    for issue in all_issues:
        if issue['file'] not in files_with_issues:
            files_with_issues[issue['file']] = []
        files_with_issues[issue['file']].append(issue)
    
    # Выводим подробный отчет по каждому файлу
    for file_path, issues in files_with_issues.items():
        print(f"\nФАЙЛ: {file_path}")
        print("-" * 100)
        
        # Сортируем проблемы по строкам
        issues.sort(key=lambda x: x['line'])
        
        for issue in issues:
            if issue['line'] > 0:
                print(f"Строка {issue['line']:4d}: {issue['issue']}")
                print(f"    {issue['content']}")
            else:
                print(f"{issue['issue']}")
                if issue['content']:
                    print(f"    {issue['content']}")
    
    # Сводная статистика
    print("\n" + "="*100)
    print("СВОДНАЯ СТАТИСТИКА:")
    print("="*100)
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
        print(f"Анализ файла: {os.path.abspath(args.path)}")
        # Для одиночного файла показываем абсолютный путь
        analyze_file(args.path, show_full_path=True)
    elif os.path.isdir(args.path):
        issues_count = analyze_directory(args.path)
        print(f"\nНайдено файлов с проблемами: {issues_count}")
    else:
        print("Ошибка: указанный путь не является файлом или директорией")
        sys.exit(1)
    
    print_summary()

if __name__ == "__main__":
    main()