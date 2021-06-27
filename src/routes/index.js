const express = require('express'); //se requiere el framework
const router = express.Router(); //se inicializa express mediante una funcion
const model = require('../model/valores')();//importa el modelo a traves de una funcion se crea la referncia al modelo
const Valor = require('../model/valores');//constante solo para el recurso de valores  del schema

//requiere una peticion y una respuesta
//a traves de funcion asyncrona para obtener los datos desde bd y visualizarlos
router.get('/', async (req, res) => {
   // res.send('DIANA - HOLA');
   const coleccion = await Valor.find(); //extrae todos los valores de la bd
   console.log(coleccion); //imprime la inf de la tabla en la consola
  res.render('index.ejs', {//renderiza a vista index de la pagina html
       coleccion  //se envian a la vista por medio de render
   }); //pagina creada em views
   //res.json(coleccion);//para postman
   //res.send(200, {message: "La informacion se ha insertado correctamente"});
});

//envia los datos a la bd  mediante post
router.post('/add/', async (req, res) => {
    const valors = new Valor(req.body); //constante para poder registrar los valores de un documento en la bd
    //envia los datos a traves de request y regresa esos datos del formulario a la tabla para ser visualizados
    await valors.save(); //guarda el registro en la bd
    res.render('index.ejs', {//renderiza a vista index de la pagina html
      valors  //se envian a la vista por medio de render
    }); //pagina creada em views
    //res.redirect('/');//redirecciona a la misma pagina principal
    //res.json(req.body);//para postman
   //res.send(200, {message: "La informacion se ha consultado"});
 });

module.exports = router; //exporta archivo index.js para ser legible y visualizado como primer url