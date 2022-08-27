const express = require('express')
const app = express()
const bodyParser = require('body-parser');
//app.use(bodyParser.urlencoded({ extended: true }));


// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: false }))

// parse application/json
app.use(bodyParser.json())

var ledState = 0;

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
  console.log("CLIENT: google assistant", req.body)
  console.log("CLIENT: POST em /sensor")
})

app.post("/setLed", function(req, res){
  console.log("CLIENT: google assistant", req.body)
  ledState = req.body["led_state"];
  console.log("CLIENT: POST em /sensor")
})

app.get("/getLed", function(req, res){
  res.send(ledState.toString())
  console.log("CLIENT: GET em /getLed")
})

//setInterval(() => {console.log(ledState)},2000);

app.get('/sensor', (req, res) => {
    console.log("CLIENT: GET em /sensor")
    res.send('SERVER: GET em sensor')
})

app.get('/', (req, res) => {
  console.log("CLIENT: GET em /")
  res.send('SERVER: hello world')
  res.status(200)
})


app.listen(3000)
