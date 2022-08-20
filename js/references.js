const fs = require('fs');

var references = {
    hello: function() {
        console.log('Nicolas');
    },

    types_example: function(){
        var _string = 'string';
        var _number = 10.1;
        var _object = {}; // or undefined
        var _undefined;

        console.log('_string', typeof(_string));
        console.log('_number', typeof(_number));
        console.log('_object', typeof(_object));
        console.log('_undefined', typeof(_undefined));
    },

    let_var_example: function() {
        var a = 5;
        var b = 10;

        if (a === 5) {
              let a = 4; // O escopo é dentro do bloco if
              var b = 1; // O escopo é dentro da função

              console.log('let a', a);  // 4
              console.log('var b', b);  // 1
            
        }

        console.log('var a', a); // 5
        console.log('var b', b); // 1
    },

    array_example: function() {
        var a = [1,2,3];

        console.log('For statement');
        for(let i = 0; i < a.length; i++) {
            console.log(a[i]);
        }
        
        a.push('jonathas');

        a.push({a:2});

        a.splice(0,1); // Removendo o primeiro elemento (index, quantidade)

        console.log('ForEach');
        a.forEach((v) => {console.log(v);});
    },

    conditionals_example: function() {
        var cond_1 = 10 > 1; // > => <= ==
        var cond_2 = 1 || 0; // & 

        console.log(cond_1, cond_2);

        if(cond_1 && cond_2) {
            console.log("True condition");
        } else {
            console.log("False condition");
        }
    },

    switch_example: function() { 
        var option = 1;
        switch(option) {
            case 1: console.log('option 1'); break;
            case 2: console.log('option 2'); break;
            default: console.log();
                
        }
    },

    scope_example: function() {
        var x = 2;
        var pow = (a) => {
            a = a *a; 
            console.log(a); 
            return a;
        };

        console.log('without return');
        pow(x);
        console.log(x);

        console.log('with return');
        var x = pow(x);
        console.log(x);

        console.log('setting x');
        var set_x = () => {x = 10;};
        //var set_y = () => {var y = 10;};
        set_x();
        console.log(x);
        //console.log(y);
    },

    class_example:
    class test {
        constructor() {
            this.z = 15; // [], {}, number, string ...
        }
        
        some_method = () => {
            this.z = this.z + 12;
        };
    },

    test_json: function () {
        var _json = { 
            a:1, 
            b: 'Jonathas', 
            c: {d:2}, 
            e: (k) => {return k + 10} 
        };
        console.log(_json);
        console.log(_json['a']);
        console.log(_json.e(20));
    },

    test_promise: function() {
        var my_promise = (duration) => { 
            return new Promise((resolve, reject) => {
                setTimeout(resolve, duration);
            });
        }
       
        my_promise(3000).then(() => {
            // Esse pedaço executa depois da função promessa
            console.log('Passou 3 segundos');
        });

        var get_users = () => {
            return new Promise((resolve, reject) => {
                // Passando um array para a função posterior
                // Após a resolução dessa promessa
                resolve([1,2,3,4,5]);
            });
        }

        get_users().then((users) => {console.log(users);});
    },

    file_example: function() {
        fs.readFile('./test.txt', 'utf8', (err, data) => {
            if (err) {
                    console.error(err);
                    return;
                  
            }
              console.log(data);
        });
    },

    json_file_example: function() { 
        let rawdata = fs.readFileSync('test.json');
        let test_json = JSON.parse(rawdata);
        console.log(test_json);
    }
}

module.exports = references;
