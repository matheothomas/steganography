# Steganography

Steganography is a small C project aiming to hide a message in a `.png` image, and to recover it.

## Principle

### Encoding
- A message is given as a string, and converted into the ASCII values of every character.
- The ASCII code is converted into a binary string.
- The least significant bit of each pixel of the image is modified (if needed) to match the binary string generated above.
- The image is exported.

### Decoding
- The least significant bit of each pixel of the image is concatened into a string of binary values.
- This string is cut into substrings of 8 bits each, and converted into decimal values, which corresponds to the ASCII codes of characters.
- A string is generated with these characters : it is the hidden message.

### Example
- Message : `Hi`
- Binary (ASCII) : `0100100001101001`
- For the first pixel, if its RGB values are `63-50-200`, in binary it is `00111111-00110010-11001000`.
- To match the beginning of the message, we change the least significant bit :
    - `00111111 -> 00111110`
    - `00110010 -> 00110011`
    - `11001000 -> 11001000`


## Code

### Features

The program can  :
- Hide a message in a given `.png` image - generates a `output.png` in the `res/` folder.
- Recover a message hidden in a given `.png` image.

### Installation
Clone the repository :
```bash
git clone https://github.com/matheothomas/steganography
```

Go into the `src` directory :
```bash
cd steganography/src
```

Compile the code :
```bash
make
```
### How to use

Execute the program :
```bash
./main
```

- With `0` you can provide an image (`tux.png` is available the `res/` folder) and then enter some text.

- With `1` you can provide a coded image to decode its hidden message.
