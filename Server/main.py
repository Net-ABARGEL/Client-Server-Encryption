# This is a Server
import os
import threading
import socket

from checkDB import check_and_create_tables
from handler import handle_req
from requestToServer import request_from_client


def handle_client(conn, addr):
    print('connected by', addr)
    while True:
        request = request_from_client(conn)  # waiting for request from the client
        if request is None:
            break
        handle_req(request, conn)  # handling the request
    print('Client has logged off', addr)    # not request from the client, sign off the client
    conn.close()


def main():
    HOST = ''
    PORT = 1357  # Defoult port

    # check DB files
    check_and_create_tables()
    # Read port from file
    if not os.path.exists("port.info"):
        print("file does not exist, will work on port 1357") # if not exist

    else:
        # reading the port from the file
        with open("port.info", "r") as file:
            # Read the first line
            PORT = file.readline().strip()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, int(PORT)))
        print("waiting for clients on port " + str(PORT))
        s.listen()

        while True:
            conn, addr = s.accept()  # waiting for client, if connected, will start the process
            client_thread = threading.Thread(target=handle_client, args=(conn, addr))
            client_thread.start()   # thread to support several clients


if __name__ == "__main__":
    main()
