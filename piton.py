from PIL import Image
import pytesseract
import time
import keyboard
import random
 
IMAGE_INPUT_NAME = 'input.jpg'
FILE_OUTPUT_NAME = 'result.txt'
ACCEPTED_ASCII_LIST = [x for x in range(32, 127)]
 
def extract_text_from_image():
    PIPE_ASCII = 124
    
    time_start = time.perf_counter()
    text = pytesseract.image_to_string(Image.open(IMAGE_INPUT_NAME))
    with open(FILE_OUTPUT_NAME, 'w') as f_out:
        for c in text:
            ascii = ord(c)
            if ascii == PIPE_ASCII:
                f_out.write('I')
            elif ascii in ACCEPTED_ASCII_LIST:
                f_out.write(c)
            else:
                f_out.write(' ')
    time_end = time.perf_counter()
    print('\nDone! Executed in: {:.2f} seconds'.format(time_end - time_start))