
# Photo Encryption

This repository contains a CLI-based tool for encrypting and decrypting image files (JPG/PNG) using the **Data Encryption Standard (DES)** algorithm. The project is implemented in both **Python** and **C++** to provide users flexibility in choosing their preferred language for usage. 

## Table of Contents
- [Features](#features)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
  - [Running the Python Version](#running-the-python-version)
  - [Running the C++ Version](#running-the-c-version)
- [Usage](#usage)
  - [Encrypting an Image](#encrypting-an-image)
  - [Decrypting an Image](#decrypting-an-image)
- [Algorithm Details](#algorithm-details)
  - [DES Encryption Modes](#des-encryption-modes)
  - [Password Derivation](#password-derivation)
- [Future Enhancements](#future-enhancements)
- [License](#license)

## Features
- **Python and C++ Implementations**: Choose between Python or C++ depending on your preference.
- **DES Encryption**: Both **ECB** and **OFB** encryption modes are supported.
- **Password-based encryption**: Generates a secure key using the user-provided password.
- **Image format support**: Works with both **JPG** and **PNG** image formats.
- **Easy to use CLI interface**.
- **Sample input image**: Provided in the repository for testing.

## Project Structure

```bash
Photo-Encryption/
│
├── cpp/                    # Contains the C++ implementation
│   ├── functions.cpp        # Contains the helper functions
│   ├── main.cpp             # Main program for encryption/decryption
│   └── Makefile             # Optional: for building the C++ program
│
├── functions.py             # Python helper functions
├── main.py                  # Python main program for encryption/decryption
├── sample_input.jpg         # A sample input image for testing
├── README.md                # This file
└── LICENSE                  # License file
```

## How It Works
This project encrypts and decrypts images using the **DES** algorithm in two modes:
1. **ECB (Electronic Codebook Mode)**: Encrypts each block of the image independently.
2. **OFB (Output Feedback Mode)**: A more secure method where each block's encryption depends on the previous one.

The process involves:
1. **User Input**: Prompting the user for an image file and a password.
2. **Key Generation**: Deriving a secure DES key from the password using the **scrypt** algorithm (Python) or **PKCS5_PBKDF2_HMAC_SHA1** (C++).
3. **Image Encryption**: Encrypting the image data using DES in either **ECB** or **OFB** mode.
4. **Image Decryption**: Reversing the process to decrypt the image with the correct password.

## Prerequisites
To run this project, you will need:
- **Python Version**:
  - Python 3.x
  - Libraries: `opencv-python`, `pycryptodome`
  
- **C++ Version**:
  - **OpenCV**: For image processing.
  - **OpenSSL**: For cryptographic operations (DES, password hashing, etc.).
  - **C++ Compiler**: `g++`, `clang`, or similar.

## Installation

### Running the Python Version

1. **Clone the repository**:
   ```bash
   git clone https://github.com/Itskindastrange/Photo-Encryption.git
   cd Photo-Encryption
   ```

2. **Install the required Python libraries**:
   ```bash
   pip install -r requirements.txt
   ```

3. **Run the Python program**:
   ```bash
   python main.py
   ```

### Running the C++ Version

1. **Navigate to the C++ directory**:
   ```bash
   cd cpp
   ```

2. **Install required libraries**:
   - **OpenCV**:
     - On Ubuntu:
       ```bash
       sudo apt-get install libopencv-dev
       ```
     - On Windows or macOS, follow [OpenCV installation guide](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html).
     
   - **OpenSSL**:
     - On Ubuntu:
       ```bash
       sudo apt-get install libssl-dev
       ```
     - For Windows/macOS, follow [OpenSSL installation guide](https://www.openssl.org/source/).

3. **Compile the Program**:
   - Use the provided `Makefile` or run:
     ```bash
     g++ -o photo_encryption main.cpp -lssl -lcrypto -lopencv_core -lopencv_imgcodecs -lopencv_highgui
     ```

4. **Run the compiled program**:
   ```bash
   ./photo_encryption
   ```

## Usage

### Encrypting an Image
To encrypt an image, run the program (Python or C++), and it will prompt for the file path and password:
```bash
Enter the path to the image file: path/to/image.jpg
Enter the password for encryption: ********
```
The encrypted file will be saved as `encrypted_ECB.bin` or `encrypted_OFB.bin`, depending on the selected encryption mode.

### Decrypting an Image
Use the same password to decrypt the image and restore the original file.

---

## Algorithm Details

### DES Encryption Modes
- **ECB (Electronic Codebook Mode)**: Each block of the image is encrypted independently. This mode can reveal some structural information about the original image.
- **OFB (Output Feedback Mode)**: A more secure method, where each block is encrypted based on the output of the previous block. This method ensures no visible patterns in the encrypted image.

### Password Derivation
- The **scrypt** algorithm (in Python) or **PKCS5_PBKDF2_HMAC_SHA1** (in C++) is used to securely derive a DES key from the user-provided password. This ensures that the password is transformed into a secure key suitable for DES encryption.

## Future Enhancements
- Add support for more encryption algorithms such as **AES**.
- Implement a graphical user interface (GUI) for ease of use.
- Add the ability to decrypt images via the CLI for more flexibility.

## License
This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.
```

