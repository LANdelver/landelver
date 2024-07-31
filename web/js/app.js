/*
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

*/

document.addEventListener('alpine:init', () => {
  
  /* Store that handles the websocket
  and the communication events for it*/
  Alpine.store('socket', {
    hasConnected: false,
    connectionFailed: false,
    socket: null,
    joinCode: null,
    connect() {
      this.socket = new WebSocket(`ws://192.168.1.${this.joinCode}:8765`);
      console.log("socket created");
      
      this.socket.addEventListener("open", (event) => {
        console.log("connection established");
        this.hasConnected = true;
      });

      this.socket.addEventListener("message", (event) => {
        this.handleMessage(event.data);
      });

      this.socket.addEventListener("error", (event) => {
        console.error('WebSocket error:', error);
      });

      this.socket.addEventListener("close", (event) => {
        console.log("connection closed");
        this.hasConnected = false;
        this.connectionFailed = true;
      });
    },
    // all outgoing messages need to go thru here
    sendMessage(message) {
      if (this.socket.readyState === WebSocket.OPEN) {
          this.socket.send(message);
      } else {
          console.error('WebSocket is not open. Ready state is:', this.connection.readyState);
      }
    },
    // all incoming messages need to be delegated here
    handleMessage(message) {
      const data = JSON.parse(message);
      if (data.type === 'requestChars') {
        Alpine.store('charHandler').handleCharacterRequest(data);
      }
    },
  });

  /* Data to handle reactivity 
  to the connect button */
  Alpine.data('connectMessage', () => ({
    connecting: false,
    connectClicked() {
      this.connecting = true;
      this.$store.socket.connectionFailed = false;
      this.$store.socket.connect();
    },
  }));

  /* Data for the user upon login
  handles if they select player or dm*/
  Alpine.data('user', () => ({
    hasSelected: false,
    isPlayer: false,
    choosePlayer() {
      this.hasSelected = true;
      this.isPlayer = true;
      console.log('requesting characters');
      const jsonMessage = JSON.stringify({ type: 'requestChars', content: '' });
      this.$store.socket.sendMessage(jsonMessage); 
    },
    chooseDm() {
      this.hasSelected = true;
      this.isPlayer = false;
    }
  }));

  /* Data for the new/existing
  character menu selection */
  Alpine.data('charMenu', () => ({
    hasSelected: false,
    pickNew: false,
    chooseNew() {
      this.hasSelected = true;
      this.pickNew = true;
    },
    chooseExisting() {
      this.hasSelected = true;
      this.pickNew = false;
    },
  }));

  // Store to handle the character requests
  Alpine.store('charHandler', {
    existingChars: [],
    handleCharacterRequest(data) {
      console.log('recieved character request');
      this.existingChars = data.chars; 
    }
  });

  // Data for all dropdown fields
  Alpine.data('dropdownState', () => ({
    // ensures the label moves up after being interacted with
    checkSelect(select) {
      if (select.value) {
        select.classList.add('has-value');
      } else {
        select.classList.remove('has-value');
      }
    },
    init() {
      this.checkSelect(this.$refs.select);
      
      // Ensure label transitions correctly on focus for mobile
      this.$refs.select.addEventListener('focus', () => {
        this.$refs.select.classList.add('has-value');
      });
      this.$refs.select.addEventListener('blur', () => {
        this.checkSelect(this.$refs.select);
      });
    }
  }));

});

