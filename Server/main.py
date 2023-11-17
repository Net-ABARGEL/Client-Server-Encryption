# This is a sample Python script.
import os
# Press ⌃R to execute it or replace it with your code.
# Press Double ⇧ to search everywhere for classes, files, tool windows, actions, and settings.

import sqlite3
import socket
import struct

from handler import handle_req
from checkDB import check_and_create_tables
from checkDB import check_name_exists

from requestToServer import request_from_client

PORT = 1357
if not os.path.exists("port.info"):
    print("file does not exist, will work on port 1357")

else:
    # reading the port from the file
    with open("port.info", "r") as file:
        # Read the first line
        PORT = file.readline().strip()

HOST = ''

check_and_create_tables()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, int(PORT)))
    print("waiting for a client in port" + str(PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('connected by', addr)
        while True:
            request = request_from_client(conn)  # in requestToServer.py
            if request is None:
                break;
            handle_req(request, conn)  # in request.py
            a = input("enter 0 to exit")
            if a == '0':
                break
            # obj = conn.recv(1024)
            # text = obj.decode("utf-8")
            # print(str(request['id']) + "\n version " + str(request['version']) + "code" + str(
            #   request['code']) + "length" + str(request['payload_length'])+"\n payload:"+str(request['payload']))
            # print(obj)
            #  obj = request_to_server(conn)
            # if obj is None:
            #   break
            break;


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press ⌘F8 to toggle the breakpoint.
