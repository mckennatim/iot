var mysql      = require('mysql');
const dev = require('./device.json')
const env = require('./env.json')
const conn= mysql.createConnection(env.mysql);


dev.description = JSON.stringify(dev.description)
dev.server = JSON.stringify(dev.server)
dev.specs = JSON.stringify(dev.specs)
console.log('dev: ', dev)


const qry = conn.query('INSERT INTO devs SET ? ON DUPLICATE KEY UPDATE ?', [dev,dev],(error,results)=>{
  console.log('error: ', error)
  console.log('results: ', results)
})




