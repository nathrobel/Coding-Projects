import threading 
import socket  # noqa: F401
import sys

directory = "."

def handle_request(client_socket):
    #globa
    global directory
    try:
        data = client_socket.recv(1024)
        requested = data.decode()
        if requested.startswith("GET / HTTP/1.1"):
            response  = "HTTP/1.1 200 OK\r\n\r\n"
        elif requested.startswith("GET /echo/"):
            path = requested.split()[1]
            message = path[len("/echo/"):]
            content_length = len(message)
            lines = requested.splitlines()
            header_lines = lines[1:]

            accept_encoding = ""
            for line in header_lines:
                if line.lower().startswith("accept-encoding:"):
                    accept_encoding = line[len("accept-encoding:"):]
                
                    break
            
            compressed_body = "empty"
                 
            if accept_encoding.strip() == "gzip":
                response = f"HTTP/1.1 200 OK\r\nContent-Encoding: {accept_encoding}\r\nContent-Type: text/plain\r\nContent-Length: {len(compressed_body)}\r\n\r\n{compressed_body}"
            else:
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




        elif requested.startswith("GET /files/"):
            path = requested.split()[1]
            filename = path[len("/files/"):]
            filepath = f"{directory}/{filename}"
            try:
                with open(filepath,"rb") as f:
                    content = f.read()
                    length = len(content)
                    headers = (f"HTTP/1.1 200 OK\r\nContent-Type: application/octet-stream\r\nContent-Length:{length} \r\n\r\n")
                    client_socket.sendall(headers.encode() + content)
                    return
                    
            except FileNotFoundError:
                response = "HTTP/1.1 404 Not Found\r\n\r\n"
                client_socket.sendall(response.encode())
                return 
        elif requested.startswith("POST /files/"):
            path = requested.split()[1]
            filename = path[len("/files/"):]
            filepath = f"{directory}/{filename}"
            header_body = requested.split("\r\n\r\n")
            

            try:
                with open(filepath,"wb") as f:
                    content = header_body[1]
                    f.write(content.encode())
                    response = (f"HTTP/1.1 201 Created\r\n\r\n")
                    client_socket.sendall(response.encode())
                    return
            except Exception as e:
                print(f"error writing file:{e}")
                response = "HTTP/1.1 500 Internal Server Error\r\n\r\n"
                client_socket.sendall(response.encode())
                return



        else:
            response  = "HTTP/1.1 404 Not Found\r\n\r\n"
        client_socket.sendall(response.encode())
    finally:
        client_socket.close()





   


def main():
    global directory 
    print("Logs from the program will appear here!")
    if len(sys.argv) > 2 and sys.argv[1] == "--directory":
        directory = sys.argv[2]

    print(f"Serving files from directory: {directory}")

    
    server_socket = socket.create_server(("localhost", 4221), reuse_port=True)
    try:
        while True:
            print("The Server is running")
            client_socket, addr = server_socket.accept()
            print(f"We have a connection from {addr}")
            t = threading.Thread(target=handle_request, args=(client_socket,))
            t.start()
            
    except KeyboardInterrupt:
        print("Halting Server")
    
    finally:
        server_socket.close()
        print("The server has been shut down")



if __name__ == "__main__":
    main()
