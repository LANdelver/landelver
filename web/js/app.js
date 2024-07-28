document.addEventListener('alpine:init', () => {
  Alpine.store('socket', {
    hasConnected: false,
    connect() {
      const socket = new WebSocket(`ws://${window.location.hostname}:8765`);
      console.log("socket created");
      
      socket.onopen = () => {
        console.log("connection established");
        this.hasConnected = true;
      };

      socket.onmessage = (event) => {
        console.log(event.data);
      };

      socket.onerror = (error) => {
        console.error('WebSocket error:', error);
        this.reconnect();
      };

      socket.onclose = () => {
        console.log("connection closed");
        this.hasConnected = false;
        this.reconnect();
      };
    },
    reconnect() {
      setTimeout(() => {
        this.connect();
      }, 5000); 
    },
    init() {
      console.log('store init');
      this.connect();
    }
  });

  Alpine.data('loadingPage', () => ({
    messages: [
      "rolling initiative...",
      "generating dungeons...",
      "brewing potions...",
      "seducing the dragon...",
      "casting fireballs...",
      "entering rage...",
      "perceiving... nothing?",
      "disarming traps...",
      "meeting in tavern...",
      "standing night watch...",
      "viciously mocking...",
      "picking pockets...",
      "speaking with animals...",
      "looting bodies...",
      "attuning magic items...",
      "reading spell scrolls...",
      "looting the bodies..."
    ],
    currentMessageIndex: 0,
    currentMessage: "rolling initiative...",
    startLoad() {
      setInterval(() => {
        this.currentMessageIndex = (this.currentMessageIndex + 1) % this.messages.length;
        this.currentMessage = this.messages[this.currentMessageIndex];
      }, 2000);
    },
    init() {
      this.startLoad();
    } 
  }));
  
  Alpine.data('user', () => ({
    hasSelected: false,
    isPlayer: false,
    choosePlayer() {
      this.hasSelected = true;
      this.isPlayer = true;
    },
    chooseDm() {
      this.hasSelected = true;
      this.isPlayer = false;
    }
  }));
});

