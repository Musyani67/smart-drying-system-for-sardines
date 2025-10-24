// backend/server.js
const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const path = require('path');


const app = express();
const server = http.createServer(app);
const io = new Server(server);


const PORT = process.env.PORT || 3000;


// Serve frontend static files
app.use(express.static(path.join(__dirname, '..', 'frontend')));


// Simple in-memory state (replace with real sensors/DB)
let state = {
temperature: 28.0, // Celsius
humidity: 55.0, // % RH
fan: false,
heater: false,
weight_kg: 5.0, // weight of sardines (example)
target_weight_kg: 2.5,
lastUpdate: new Date().toISOString()
};


// helper: simulate sensor changes
function simulateStep() {
// small random walk for temp/humidity
state.temperature += (Math.random() - 0.48) * 0.4;
state.humidity += (Math.random() - 0.5) * 0.7;


// clamp
state.temperature = Math.max(10, Math.min(60, state.temperature));
state.humidity = Math.max(5, Math.min(100, state.humidity));


// drying: weight slowly decreases if temperature > 25 and humidity < 60
const dryingRate = (state.temperature > 25 && state.humidity < 65 && state.fan) ? 0.01 : 0.002;
state.weight_kg = Math.max(0.1, state.weight_kg - dryingRate);


// simple rules for actuators (demo)
state.fan = state.humidity > 60 || state.temperature > 35;
state.heater = state.temperature < 20 && state.weight_kg > state.target_weight_kg;


state.lastUpdate = new Date().toISOString();
}


// Simulate sensors every 2s
setInterval(() => {
simulateStep();
// broadcast state
io.emit('status', state);
}, 2000);


// REST endpoint for current status (fallback polling)
app.get('/api/status', (req, res) => {
res.json(state);
});


// Allow clients to request actuator changes (demo only)
app.post('/api/actuators/:name/:value', express.json(), (req, res) => {
const { name, value } = req.params;
if (name in state) {
// only allow toggling fan/heater in demo
if (name === 'fan' || name === 'heater') {
state[name] = value === '1' || value === 'true';
state.lastUpdate = new Date().toISOString();
io.emit('status', state);
return res.json({ ok: true, state });
}
}
res.status(400).json({ ok: false, message: 'invalid actuator' });
});


// Socket.IO connection
io.on('connection', (socket) => {
console.log('client connected', socket.id);
// send current state on connect
socket.emit('status', state);


socket.on('disconnect', () => {
console.log('client disconnected', socket.id);
});
});


server.listen(PORT, () => console.log(`Monitor server listening on http://localhost:${PORT}`));