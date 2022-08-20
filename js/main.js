const fs = require('fs');

let rawdata = fs.readFileSync('input.json');
let input_json = JSON.parse(rawdata);

function mode_1(input_json) {
    console.log(input_json)
    console.log("Energia", (input_json["power"]*0.001) * (input_json["cycles"] / (input_json["frequency"] * 1000000)));
}

function mode_3(input_json) {
    console.log(input_json);
    var r_all = 0;
    input_json.resistences.forEach((e) => {r_all += 1/e;});
    r_all = 1 / r_all;
    console.log("r_all", r_all);
    var I = input_json['voltage'] / r_all;
    console.log(I);
}

function mode_2(input_json) {
    console.log(input_json);
    var r_all = 0;
    input_json.resistences.forEach((e) => {r_all += e;});
    console.log('r_all', r_all);
    var I = input_json['voltage'] / r_all;
    console.log(I);
}

switch(input_json['option']) {
    case 1: 
        console.log('option 1');
        mode_1(input_json);
        break;
    case 2:
        console.log('option 2');
        mode_2(input_json);
        break;
    case 3: 
        console.log('option 3'); 
        mode_3(input_json);
        break;
    default: console.log();
}
