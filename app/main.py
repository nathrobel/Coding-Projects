import socket  # noqa: F401


def handle_request(client_socket):
    client_socket.recv(1024)
    response  = "HTTP/1.1 200 OK\r\n\r\n"
    client_socket.send(response.encode())


   


def main():
    # You can use print statements as follows for debugging, they'll be visible when running tests.
    print("Logs from your program will appear here!")

    # Uncomment this to pass the first stage
    #
    
    server_socket = socket.create_server(("localhost", 4221), reuse_port=True)
    try:
        while True:
            print("The Server is running")
            client_socket, addr = server_socket.accept()
            print(f"We have a connection from {addr}")
            handle_request(client_socket)
            client_socket.close()
    except KeyboardInterrupt:
        print("Halting Server")
    
    finally:
        server_socket.close()
        print("The server has been shut down")



if __name__ == "__main__":
    main()
