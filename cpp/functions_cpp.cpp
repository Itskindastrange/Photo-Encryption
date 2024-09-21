#include <opencv2/opencv.hpp>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Function to load the image using OpenCV
cv::Mat loadImg(const string &path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR); // Load in RGB format
    if (img.empty()) {
        cerr << "Could not load image!" << endl;
        exit(1);
    }
    return img;
}

// Function to flatten image data into a single array
vector<uint8_t> flattenImg(const cv::Mat &img) {
    vector<uint8_t> flatData;
    flatData.assign(img.data, img.data + img.total() * img.channels());
    return flatData;
}

// Function to generate a DES key using OpenSSL
vector<uint8_t> DES_Key(const string &password, const vector<uint8_t> &salt) {
    vector<uint8_t> key(8); // DES key is 8 bytes
    if (!PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), password.length(), salt.data(), salt.size(), 16384, 8, key.data())) {
        cerr << "Key generation failed!" << endl;
        exit(1);
    }
    return key;
}

// Function to initialize DES in OFB mode and return the cipher context
DES_key_schedule OFB(const vector<uint8_t> &key, vector<uint8_t> &iv) {
    DES_key_schedule schedule;
    DES_set_key_unchecked(reinterpret_cast<const_DES_cblock*>(key.data()), &schedule);

    // Generate a random IV
    iv.resize(DES_KEY_SZ);
    if (!RAND_bytes(iv.data(), DES_KEY_SZ)) {
        cerr << "IV generation failed!" << endl;
        exit(1);
    }
    return schedule;
}

// Function to encrypt data using DES (ECB or OFB modes)
vector<uint8_t> encryptImg(const vector<uint8_t> &data, const DES_key_schedule &schedule, const string &mode, const vector<uint8_t> &iv = {}) {
    vector<uint8_t> encryptedData(data.size());
    
    if (mode == "ECB") {
        for (size_t i = 0; i < data.size(); i += DES_KEY_SZ) {
            DES_ecb_encrypt(reinterpret_cast<const_DES_cblock*>(&data[i]), reinterpret_cast<DES_cblock*>(&encryptedData[i]), &schedule, DES_ENCRYPT);
        }
    } else if (mode == "OFB") {
        unsigned char tempIv[DES_KEY_SZ];
        memcpy(tempIv, iv.data(), DES_KEY_SZ);
        DES_ofb64_encrypt(data.data(), encryptedData.data(), data.size(), &schedule, reinterpret_cast<DES_cblock*>(tempIv), nullptr);
    }

    return encryptedData;
}

// Function to save binary data to a file
void saveBinary(const vector<uint8_t> &data, const string &filePath) {
    ofstream outFile(filePath, ios::binary);
    outFile.write(reinterpret_cast<const char*>(data.data()), data.size());
    outFile.close();
}

// Function to display original and encrypted images
void displayImgs(const cv::Mat &original, const vector<uint8_t> &encryptedECB, const vector<uint8_t> &encryptedOFB, const cv::Size &originalSize) {
    // Create OpenCV Mat objects for encrypted images
    cv::Mat ecbImg = cv::Mat(originalSize, CV_8UC3, (void*)encryptedECB.data());
    cv::Mat ofbImg = cv::Mat(originalSize, CV_8UC3, (void*)encryptedOFB.data());

    // Display images
    cv::imshow("Original Image", original);
    cv::imshow("ECB Encrypted Image", ecbImg);
    cv::imshow("OFB Encrypted Image", ofbImg);
    cv::waitKey(0);
}
