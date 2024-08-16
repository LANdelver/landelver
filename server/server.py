"""
Copyright (C) 2024 Lance Borden, Sariah Echols

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3.0
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.

"""

import asyncio
import base64
import os
import websockets
import socket
import json

current_campaign = "demo"

# Function to get the LAN IP address of the current machine
def get_lan_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # connect() for UDP doesn't send packets
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
    except Exception:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip

async def handle_message(websocket, message):
    json_data = json.loads(message)
    if json_data['type'] == "requestChars":
        packet = '{"type":"requestChars", "chars":["boblin", "clifford"]}'
        await websocket.send(packet)

    elif json_data['type'] == "sendCharacter":
        header = json_data['image']['header']
        raw_data = json_data['image']['raw']
        player_name = json_data['character']['name']  # Extract the player's name
        file_path = save_image(header, raw_data, player_name)
        save_character_json(json_data['character'], player_name)
        print(f"Image saved to: {file_path}")

def save_character_json(data, player_name):
    with open(f'../table/resources/players/{player_name}.json', 'w') as f:
        json.dump(data, f)

# Function to save image data
def save_image(header, raw_data, player_name):
    # Create the uploads directory if it doesn't exist
    upload_dir = "../table/resources/players"
    if not os.path.exists(upload_dir):
        os.makedirs(upload_dir)

    # Extract the image type from the header (e.g., 'png')
    file_extension = header.split('/')[1].split(';')[0]

    # Generate the file name using the player's name
    file_name = f"{player_name}.{file_extension}"
    file_path = os.path.join(upload_dir, file_name)

    # Decode the base64 image data
    image_data = base64.b64decode(raw_data)

    # Write the image data to the file
    with open(file_path, "wb") as image_file:
        image_file.write(image_data)

    return file_path


# Define a callback function to handle incoming WebSocket messages
async def handle_websocket(websocket):
    try:
        while True:
            message = await websocket.recv()
            print(f"Received message: {message}")
            await handle_message(websocket, message)

    except websockets.ConnectionClosed:
        pass

if __name__ == "__main__":
    # Start the WebSocket server
    lan_ip = get_lan_ip()
    print(f"Starting websocket server on {lan_ip}:8765")
    start_server = websockets.serve(handle_websocket, lan_ip, 8765)

    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()
