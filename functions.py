import numpy as np
from PIL import Image
from Crypto.Cipher import DES
from Crypto.Protocol.KDF import scrypt
from Crypto.Util.Padding import pad, unpad
import tkinter as tk
from tkinter import filedialog
import matplotlib.pyplot as plt

def selectFile():
    root = tk.Tk()
    root.withdraw()
    filePath = filedialog.askopenfilename(
        title="Select an image file",
        filetypes=[("Image files", ".jpg .jpeg .png")]
    )
    if filePath:
        print(f"Selected file: {filePath}")
        return filePath
    else:
        print("No file selected")
        return None

def loadImg(path):
    img = Image.open(path)
    img = img.convert('RGB')
    arrData = np.array(img)
    return arrData, img

def flattenImg(arrData):
    return arrData.flatten()

def DES_Key(userPassword, salt=b'somesalt'):
    keyLength = 8 
    key = scrypt(userPassword.encode(), salt, keyLength, N=2**14, r=8, p=1)
    return key


def OFB(key):
    cipher = DES.new(key, DES.MODE_OFB)
    return cipher, cipher.iv 

def encryptImg(data, key, mode):
    cipher = DES.new(key, mode)
    paddedData = pad(data, DES.block_size)
    return cipher.encrypt(paddedData)


def saveBinary(data, opPath):
    with open(opPath, 'wb') as f:
        f.write(data)

def loadBinary(opPath):
    with open(opPath, 'rb') as f:
        return f.read()



def displayImgs(original, encryptedECB, encryptedOFB, orignalSize):
    fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(10, 5))


    ax1.imshow(original)
    ax1.set_title('Original Image')
    ax1.axis('off')

    
    ecbArray = np.frombuffer(encryptedECB, dtype=np.uint8)
    ecbImg = ecbArray[:orignalSize[0] * orignalSize[1] * 3].reshape(orignalSize[1], orignalSize[0], 3)
    ax2.imshow(ecbImg)
    ax2.set_title('ECB Encrypted Image')
    ax2.axis('off')

    
    ofbArray = np.frombuffer(encryptedOFB[8:], dtype=np.uint8)  
    ofbImg = ofbArray[:orignalSize[0] * orignalSize[1] * 3].reshape(orignalSize[1], orignalSize[0], 3)
    ax3.imshow(ofbImg)
    ax3.set_title('OFB Encrypted Image')
    ax3.axis('off')

    plt.tight_layout()
    plt.show()
