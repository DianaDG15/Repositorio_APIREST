const mongoose = require('mongoose');//requiere mongoose para realizar la conexion a bd
const Schema = mongoose.Schema; //se crea esquema de tipo mongoose

//estructura del documento que se inserta en mongobd con los datos 
//registrados por el usuario
const Valor = new Schema({
    Temperatura: String,
    Humedad: String,
    Distancia: String, 
    Crecimiento: String,
    Fecha: { type:Date, default:Date.now}
});

//se exporta un modulo como modelo ya que permite 
//crear, actualizar, eliminar, leer, todos los valores 
module.exports = mongoose.model('coleccion', Valor);