﻿#include <string>
#include <iomanip>

#include "BinToDec.h"
#include "ConsolePresentation.h"
#include "DecToBin.h"

template<class T>
ostream& operator<<(ostream& out, const vector<T>& a) {
    for (int i = 0; i < a.size(); ++i)
        out << a[i];
    return out;
}

int main() {
    int choice = 0;
    bool firstTime = true;
    cout << "WELCOME TO BINARY CONVERT\n\nChoose what you want to do\n";
    cout << "1. Decimal convert to Binary\n2. Binary convert to Decimal\n3. Exit program\n\n";
    cout << "Enter your choice (1/2/3): ";
    while (choice != 1 && choice != 2 && choice != 3) {
        cin >> choice;
        firstTime = false;
        if (choice != 1 && choice != 2 && choice != 3 && !firstTime) {
            system("cls");
            cout << "WELCOME TO BINARY CONVERT\n\nChoose what you want to do\n";
            cout << "1. Decimal convert to Binary\n2. Binary convert to Decimal\n3. Exit program\n\n";
            cout << "Wrong choice. Let's try again\n";
            cout << "Enter your choice (1/2/3): ";
        }
    }
    if (choice == 3) cout << "\nGood Bye ^^";
    else if (choice == 1) {
        system("cls");
        cout << "WELCOME TO BINARY CONVERT\n\n1. Decimal convert to Binary\n";
        cout << "Let's enter your value: ";
        double x;
        cin >> x;
        cout << "\nSingle precision floating-point: " << Presentation::representOutputBitSequence(DoubleToBin::to32Bit(x));
        cout << "\n\nDouble precision floating-point: " << Presentation::representOutputBitSequence(DoubleToBin::to64Bit(x));
        cout << "\n\nUnsigned interger 8 bits: " << Presentation::representOutputBitSequence(IntegerToBin::to8Bit(x));
        try {
            cout << "\n\nInterger 8 bits: " << Presentation::representOutputBitSequence(IntegerToBin::to2s8Bit(x));
        }
        catch (runtime_error ex) {
            cout << ex.what();
        }
        cout << "\n\nUnsigned interger 16 bits: " << Presentation::representOutputBitSequence(IntegerToBin::to16Bit(x));
        try {
            cout << "\n\nInterger 16 bits: " << Presentation::representOutputBitSequence(IntegerToBin::to2s16Bit(x));
        }
        catch (runtime_error ex) {
            cout << ex.what();
        }
        cout << "\n\nUnsigned interger 32 bits: " << Presentation::representOutputBitSequence(IntegerToBin::to32Bit(x));
        try {
            cout << "\n\nInterger 32 bits: " << Presentation::representOutputBitSequence(IntegerToBin::to2s32Bit(x));
        }
        catch (runtime_error ex) {
            cout << ex.what();
        }
    }
    else {
        system("cls");
        cout << "WELCOME TO BINARY CONVERT\n\n2. Binary convert to Decimal\n";
        cout << "Let's choose your length of binary sequence (8/16/32/64 bits)\n";
        cout << "1. 8 bits\t2. 16 bits\t3. 32 bits\t4. 64 bits\n";
        cout << "Your choice: ";
        while (true) {
            cin >> choice;
            int length;
            if (choice == 1) length = 8;
            else if (choice == 2) length = 16;
            else if (choice == 3) length = 32;
            else if (choice == 4) length = 64;
            else {
                system("cls");
                cout << "WELCOME TO BINARY CONVERT\n\n2. Binary convert to Decimal\n";
                cout << "Let's choose your length of binary sequence (8/16/32/64 bits)\n";
                cout << "1. 8 bits\t2. 16 bits\t3. 32 bits\t4. 64 bits\n";
                cout << "Your choice: ";
                continue;
            }
            break;
        }
        cout << "Enter your binary sequence: ";
        string bin;
        cin >> bin;
        CheckBinarySequence check;
        while (!check.isValid(bin)) {
            system("cls");
            cout << "WELCOME TO BINARY CONVERT\n\n2. Binary convert to Decimal\n";
            cout << "The length of binary sequence: ";
            if (choice == 1) cout << "8 bits\n";
            else if (choice == 2) cout << "16 bits\n";
            else if (choice == 3) cout << "32 bits\n";
            else if (choice == 4) cout << "64 bits\n";
            cout << "Enter your binary sequence: ";
            cin >> bin;
        }
        int len = 0;
        system("cls");
        cout << "WELCOME TO BINARY CONVERT\n\n2. Binary convert to Decimal\n";
        cout << "The length of binary sequence: ";
        if (choice == 1) {
            cout << "8 bits\n";
            len = 8;
        }
        else if (choice == 2) {
            cout << "16 bits\n";
            len = 16;
        }
        else if (choice == 3) {
            cout << "32 bits\n";
            len = 32;
        }
        else if (choice == 4) {
            cout << "64 bits\n";
            len = 64;
        }
        if (len == 8 || len == 16) {
            BinaryToInteger bti(len, bin);
            cout << Presentation::representInputBitSequence(bti.numberOfBit(), bti.binarySequence());
            cout << "\n\nUnsigned integer: " << bti.convertToUnsignedInteger();
            cout << "\n\nSigned integer: " << bti.convertToSignedInteger();
        }
        else if (len == 32) {
            BinaryToInteger bti(len, bin);
            BinaryToFloatingPoint btf(len, bin);
            cout << Presentation::representInputBitSequence(bti.numberOfBit(), bti.binarySequence());
            cout << "\n\nUnsigned integer: " << bti.convertToUnsignedInteger();
            cout << "\n\nSigned integer: " << bti.convertToSignedInteger();
            cout << fixed << setprecision(5) << "\n\nFloat: " << btf.convertToSinglePrecisionFloat();
        }
        else if (len == 64) {
            BinaryToFloatingPoint btf(len, bin);
            cout << Presentation::representInputBitSequence(btf.numberOfBit(), btf.binarySequence());
            cout << fixed << setprecision(5) << "\nDouble: " << btf.convertToDoublePrecision();
        }
    }
    return 0;
}
// g++ BinToDec.cpp BinToDec.h ConsolePresentation.cpp ConsolePresentation.h DecToBin.cpp DecToBin.h main.cpp