# Steganography

Steganography is a small C project aiming to hide a message in a `.png` image, and to recover it.

## Principle
The program can  :
- Hide a message in a given `.png` image - generates a `output.png` in the `res/` folder.
- Recover a message hidden in a given `.png` image.


## Installation
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
## How to use

Execute the program :
```bash
./main
```

- With `0` you can provide an image (`tux.png` is available the `res/` folder) and then enter some text.

- With `1` you can provide a coded image to decode its hidden message.
