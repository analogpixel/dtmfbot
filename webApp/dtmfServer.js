// https://github.com/visionmedia/express
// http://expressjs.com/
// http://socket.io/

var express = require('express');

var app = require('express')()
  , server = require('http').createServer(app)
  , io = require('socket.io').listen(server);

io.set('log level', 0);
app.use( express.static(__dirname + '/public') );

/*
app.all('/api/set/:KEY/:VALUE', function(req,res) {
  globalVars[req.params.KEY] = req.params.VALUE;
  io.sockets.in('global').emit('updateVar', { key:req.params.KEY, value: req.params.VALUE });
  res.send(req.params.VALUE);
});
*/

app.get('/cmd/:cmd', function(req,res) {
    io.sockets.in('global').emit('cmd', req.params.cmd);
    res.send("ok");
});

// add the socket to the global pool
io.sockets.on('connection', function (socket) {
              socket.join('global');
});

// add the socket to the global pool
io.sockets.on('disconnect', function (socket) { socket.leave('global'); });

server.listen(8000);
