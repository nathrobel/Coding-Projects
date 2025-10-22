import socket  # noqa: F401


def handle_request(client_socket):
    data = client_socket.recv(1024)
    requested = data.decode()
    if requested.startswith("GET / HTTP/1.1"):
        response  = "HTTP/1.1 200 OK\r\n\r\n"
    elif requested.startswith("GET /echo/"):
        path = requested.split()[1]
        message = path[len("/echo/"):]
        content_length = len(message)
        response = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: {content_length}\r\n\r\n{message}"
    elif requested.startswith("GET /user-agent"):
        lines  = requested.splitlines()
        user_agent_val = ""
        for line in lines:
            if line.lower().startswith("user-agent"):
                user_agent_val = line[11:].strip()
                break
            else:
                continue

        user_agent_val_length = len(user_agent_val)
        response = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: {user_agent_val_length}\r\n\r\n{user_agent_val}"

    else:
        response  = "HTTP/1.1 404 Not Found\r\n\r\n"
    client_socket.sendall(response.encode())





   


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
