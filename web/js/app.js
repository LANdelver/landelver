document.addEventListener('alpine:init', () => {
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
    sendMessage(message) {
      if (this.socket.readyState === WebSocket.OPEN) {
          this.socket.send(message);
      } else {
          console.error('WebSocket is not open. Ready state is:', this.connection.readyState);
      }
    },
    handleMessage(message) {
      const data = JSON.parse(message);
      if (data.type === 'requestChars') {
        Alpine.store('charHandler').handleCharacterRequest(data);
      }
    },
  });

  Alpine.data('connectMessage', () => ({
    connecting: false,
    connectClicked() {
      this.connecting = true;
      this.$store.socket.connectionFailed = false;
      this.$store.socket.connect();
    },
  }));

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

  Alpine.store('charHandler', {
    existingChars: [],
    handleCharacterRequest(data) {
      console.log('recieved character request');
      this.existingChars = data.chars; 
    }
  });

  Alpine.data('dropdownState', () => ({
    checkSelect(select) {
      if (select.value) {
        select.classList.add('has-value');
      } else {
        select.classList.remove('has-value');
      }
    },
    init() {
      this.checkSelect(this.$refs.select);
    }
  }));

});

