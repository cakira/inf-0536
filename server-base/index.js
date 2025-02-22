const express = require('express')
const app = express()
const bodyParser = require('body-parser');
//app.use(bodyParser.urlencoded({ extended: true }));


// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: false }))

// parse application/json
app.use(bodyParser.json())

var ledState = 'off';
var ledFeedback = 'off';
var counter = 0;
var sleep_seconds = 1;

// npm install cors
// https://celke.com.br/artigo/como-permitir-acesso-a-api-com-cors-parte-7
const cors = require('cors');

app.use((req, res, next) => {
	  // Qual site tem permissão de realizar a conexão, no exemplo abaixo está o "*" indicando que qualquer site pode fazer a conexão
    res.header("Access-Control-Allow-Origin", "*");
	  // Quais são os métodos que a conexão pode realizar na API
    res.header("Access-Control-Allow-Methods", 'GET,PUT,POST,DELETE');
    app.use(cors());
    next();
});

app.post("/sensor", function(req, res){
  console.log("CLIENT: POST em /sensor:", req.body)
})

app.post("/setLed", function(req, res){
  j = JSON.parse(JSON.stringify(req.body))
  console.log("CLIENT: POST em /setLed:", j)
  ledState = j["led_state"];
  res.sendStatus(200)
})

app.get("/getLed", function(req, res){
  res.send(ledState.toString())
  res.status(200)
  console.log("CLIENT: GET em /getLed")
})

app.get("/getSensorState", function(req, res){
  state = ledState.toString() + "," + sleep_seconds.toString();
  res.send(state)
  res.status(200)
  console.log("CLIENT: GET em /getLed")
})

app.post("/setLedFeedback", function(req, res){
  j = JSON.parse(JSON.stringify(req.body))
  console.log("CLIENT: POST em /setLedFeedback: ", j)
  ledFeedback = j["led_state"];
  res.sendStatus(200)
})

app.get("/getLedFeedback", function(req, res){
  res.send(ledFeedback.toString())
  res.status(200)
  console.log("CLIENT: GET em /getLedFeedback")
})

app.post("/setSleep", function(req, res){
  j = JSON.parse(JSON.stringify(req.body))
  console.log("CLIENT: POST em /setSleep: ", j)
  sleep_seconds = j["sleep_time"];
  res.sendStatus(200)
})

app.get('/', (req, res) => {
  console.log("CLIENT: GET em /")
  fs = require('fs')
  fs.readFile('../client-base/controle.html', 'utf8', function (err,data) {
    if (err) {
      res.send('404: Page not found')
      res.status(404)
      console.log(err);
    }
    res.send(data);
    res.status(200)
  });
})


app.listen(3000)
console.log("Client started")
