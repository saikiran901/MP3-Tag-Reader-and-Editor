# MP3-Tag-Reader-and-Editor
MP3 Tag Reader and Editor developed in C to view and modify ID3v2 metadata such as title, artist, album, year, and comments using file handling and bitwise operations.

# 🎵 MP3 Tag Reader and Editor in C

## 📌 Overview

The **MP3 Tag Reader and Editor** is a command-line application developed using C programming. It allows users to read and modify metadata stored in MP3 audio files using the ID3v2 tag format.

The application helps users view existing MP3 information and edit specific metadata fields without modifying the actual audio content.

## ✨ Features

- **View MP3 Tags:** Display metadata information from MP3 files.
- **Edit Title:** Modify the song title.
- **Edit Artist:** Update the artist name.
- **Edit Album:** Change the album name.
- **Edit Year:** Modify the release year.
- **Edit Genre/Comment:** Update supported metadata fields.
- **File Handling:** Read and write MP3 metadata using file operations.
- **Command-Line Interface:** Perform operations through command-line arguments.

## 🛠️ Technologies Used

- C Programming
- File Handling
- Structures
- Pointers
- Bitwise Operations
- String Handling
- ID3v2 Metadata Format

## ⚙️ Supported Operations

### 1. View MP3 Information

Displays the existing metadata of an MP3 file.

```bash
./a.out -v sample.mp3
```

### 2. Edit MP3 Information

Modify specific metadata fields using the following options:

| Option | Description |
|---|---|
| `-t` | Edit Title |
| `-a` | Edit Artist |
| `-A` | Edit Album |
| `-y` | Edit Year |
| `-C` | Edit content type |
| `-c` | Edit Comments | 

**Example:**

```bash
./a.out -e -t "New Song Title" sample.mp3
```

### 3. Help

Display the available commands and usage instructions.

```bash
./a.out --help
```

## 💻 How to Compile and Run

**Step 1:** Clone the repository.

```bash
git clone <your-repository-url>
```

**Step 2:** Navigate to the project directory.

```bash
cd MP3-Tag-Reader-and-Editor
```

**Step 3:** Compile the source files.

```bash
gcc *.c -o mp3tag
```

**Step 4:** Run the application.

```bash
./mp3tag -v sample.mp3
```

## 🎯 Learning Outcomes

Through this project, I gained practical experience in:

- Understanding MP3 metadata and ID3v2 tags.
- Performing file operations in C.
- Reading and modifying binary file data.
- Working with hexadecimal values and bitwise operations.
- Handling command-line arguments.
- Implementing structured and modular programming.

## 👨‍💻 Author

**Sai Kiran Velanati**

ECE Graduate | C Programming | Embedded Systems | Data Structures

---

⭐ If you find this project useful, consider giving it a star!
