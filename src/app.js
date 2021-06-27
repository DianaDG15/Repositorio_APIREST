const express = require('express'); // requiere express como framework del proyecto
const app = express(); //inicializa express
const log = require('morgan'); //para reconocer el cliente conectado
const bodyParser = require('body-parser'); //para eejecutar get post
const path = require('path');//obtiene la ruta de inicio del proyecto
const mongoose = require('mongoose');//para conectar a mongodb
const indexRoutes = require('./routes/index.js'); ///ruta principal a ejecutar al ingresar al servidor

//escuchar servidor
app.set('port', process.env.PORT || 3000);//establecer puerto
app.set('views', path.join(__dirname, 'views')); //se indica donde estan las vistas y pagina principal 
//dirname es el archivo origen del proyecto
app.set('view engine', 'ejs'); //ruta leera archivos con extension ejs

//conexion a cluster con mongodb
//cadena de conexion usuario, contrasena y coleccion
mongoose.connect('mongodb+srv://Diana:NKssO9SNWVju4tka@iotcluster.ttib0.mongodb.net/iot?retryWrites=true&w=majority')
.then(bd => console.log('Base de Datos conectada')).catch(err => console.log(err));//si funciona la terminal muestra el mensaje
//sino imprime el error

//middleware 
//funcion que se ejecuta al realizar peticion al servidor
app.use(log('dev')); //manda llamar la ruta principal
app.use(bodyParser.urlencoded({extended:false}));//leer peticion post

//rutas 
app.use('/', indexRoutes); //direccion url a donde apunta la funcion

//configuracion del puerto
app.listen(app.get('port'), () =>{
    //imprime mensaje en la consola
    console.log('Servidor conectado en el puerto', app.get('port'))
});