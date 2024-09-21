#include "functions.cpp"
#include <iostream>

using namespace std;

int main() {
    // Get the file path from the user
    string filePath;
    cout << "Enter the path to the image file: ";
    getline(cin, filePath);

    if (filePath.empty()) {
        cerr << "No file selected." << endl;
        return 1;
    }

    // Get the encryption password
    string password;
    cout << "Enter the password for encryption: ";
    getline(cin, password);

    // Load the image
    cv::Mat img = loadImg(filePath);
    cv::Size originalSize = img.size();
    vector<uint8_t> flatData = flattenImg(img);

    // Generate the DES key
    vector<uint8_t> salt = {'s', 'o', 'm', 'e', 's', 'a', 'l', 't'};
    vector<uint8_t> key = DES_Key(password, salt);

    // Encrypt with ECB mode
    DES_key_schedule ecbSchedule;
    DES_set_key_unchecked(reinterpret_cast<const_DES_cblock*>(key.data()), &ecbSchedule);
    vector<uint8_t> encryptedBytes_ECB = encryptImg(flatData, ecbSchedule, "ECB");
    saveBinary(encryptedBytes_ECB, "encrypted_ECB.bin");

    // Encrypt with OFB mode
    vector<uint8_t> iv;
    DES_key_schedule ofbSchedule = OFB(key, iv);
    vector<uint8_t> encryptedBytes_OFB = encryptImg(flatData, ofbSchedule, "OFB", iv);
    saveBinary(encryptedBytes_OFB, "encrypted_OFB.bin");

    cout << "Encryption complete! Encrypted files saved as 'encrypted_ECB.bin' and 'encrypted_OFB.bin'." << endl;

    // Display the images
    displayImgs(img, encryptedBytes_ECB, encryptedBytes_OFB, originalSize);

    return 0;
}
