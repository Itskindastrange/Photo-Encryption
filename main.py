from Crypto.Util.Padding import pad
from Crypto.Cipher import DES
import numpy as np
import functions



filePath = functions.selectFile()
if not filePath:
    exit()

password = input("Enter the password for encryption: ")
key = functions.DES_Key(password)


data, img = functions.loadImg(filePath)
orignalSize = img.size
flattenedData = functions.flattenImg(data)
imgBytes = bytes(flattenedData)


encryptedBytes_ECB = functions.encryptImg(imgBytes, key, DES.MODE_ECB)
functions.saveBinary(encryptedBytes_ECB, 'encrypted_ECB.bin')


cipherOFB, iv = functions.OFB(key) 
encryptedBytes_OFB = iv + cipherOFB.encrypt(pad(imgBytes, DES.block_size))  
functions.saveBinary(encryptedBytes_OFB, 'encrypted_OFB.bin')

print(f"Encryption complete!\nEncrypted files saved as 'encrypted_ECB.bin' and 'encrypted_OFB.bin'.")


functions.displayImgs(np.array(img), encryptedBytes_ECB, encryptedBytes_OFB, orignalSize)
