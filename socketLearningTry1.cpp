// socketLearningTry1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//Include for Winsocket(asyncsock)  include add -> project\linker\input "WS2_32.lib" && Properties -> Configuration Properties -> Advanced -> Use of MFC -> use in shared DLL
#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
//endofInclude Winsock

using namespace std;
int main()
{
    SOCKET serverSocket, acceptSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        cout << "Winsock DLL not Found !"<<endl;
        return -1;
    }
    else {
        cout << "Winsock DLL Found !"<<endl;
        cout << "Status: " << wsaData.szSystemStatus<<endl;
    }
    //start define socket
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error Initializing Not Succeed"<<WSAGetLastError()<<endl;
        WSACleanup();
        return -2;
    }
    else {
        cout << "Socket is Fine  !!! ===INITSUCCESSS==="<<endl;
    }
    //end define socket
    
    //start bind Socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "Binding Socket Error :" << WSAGetLastError() << endl;
        WSACleanup();
        return -3;
    }
    else {
        cout << "Binding Socket OK!"<<endl;
    }
    //end Bind Socket
    //Start Listen
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cout << "Initiate Listen ServerSocket Error :" << WSAGetLastError << endl;
        WSACleanup();
        return -4;
    }
    else {
        cout << "Initiate Listen ServerSocket Success !!!" << endl;
    }
    //End Listen Procedure
    //AcceptSocket Procedure To Accept ServerSocket
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
        cout << "Accepting ServerSocket Error !!" << WSAGetLastError()<<endl;
        WSACleanup();
        return -5;
    }
    else {
        cout << "Accepting ServerSocket By AcceptSocket  is Successfull" << endl;
    }
    //end AcceptSocket PRocedure
    
    //receive data 
    char data[200];
    int reclen = recv(acceptSocket, data, 200, 0);
    if (reclen > 0) {
        cout << "data Received from  client : " << reclen << endl;
        cout << "Data is : " << data << endl;
    }
    else {
        cout << "Not Receiving ANy Data From CLient" << endl;
    }
    //end receive
    
    cout << "End of Programs";
    return 1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
