'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }
 
  let uploadFile = req.files.uploadFile;
 
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      console.log("ERROR");
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 


let sharedLib = ffi.Library('./libsvgparse', {
  'isValid': [ 'int', ['string'] ],		//return type first, argument list second
									//for void input type, leave argument list empty
  'getNumRects': [ 'int', [ 'string' ] ],	//int return, string argument
  'getNumCircs': [ 'int', [ 'string' ] ],
  'getNumPaths': [ 'int', [ 'string' ] ],
  'getNumGroups': [ 'int', [ 'string' ] ],
  'getDesc' : [ 'string', [ 'string' ] ],
  'getTitle' : [ 'string', [ 'string' ] ],
  'getAllRects': [ 'string', [ 'string' ] ],
  'getAllCircs': [ 'string', [ 'string' ] ],
  'getAllPaths': [ 'string', [ 'string' ] ],
  'getAllGroups': [ 'string', [ 'string' ] ],
  'getAllAtts': [ 'string', [ 'string', 'string' ] ],//editAtts
  'editAtts': [ 'int', [ 'string', 'string','string','string' ] ],
  'editTitle': [ 'int', [ 'string', 'string' ] ],
  'editDesc': [ 'int', [ 'string', 'string' ] ],
  'addRect': [ 'int', [ 'string', 'string' ] ],
  'addCirc': [ 'int', [ 'string', 'string' ] ],
  'addPath': [ 'int', [ 'string', 'string' ] ],
  'createSvg': [ 'int', [ 'string' ] ],
  'scaleRect': [ 'int', [ 'string', 'float' ] ],
  'scaleCirc': [ 'int', [ 'string', 'float' ] ],
});

//Sample endpoint

app.get('/list', function(req , res){
  var text = "";
  text += "<option value = \"\">" + "Select One" + "</option><br>";
  fs.readdirSync('uploads/').forEach(file => {
    let x = sharedLib.isValid(path.join('uploads/' + file));
    if(x == 1){
      text += "<option value = "+file+">" + file + "</option><br>";
    }
    //text += "<img src = "+file+"><br>";
  });
  res.send({
    foo: text
  });
});

app.get('/log', function(req , res){
  var text = "<table>";
  var cnt = 0;
  text += "<tr>" + "<th>Image<br>(Click to Download)</th>";
  text += "<th>File Name<br>(Click to Download)</th>";
  text += "<th>File Size</th>";
  text += "<th>Number of Rectangles</th>";
  text += "<th>Number of Circles</th>";
  text += "<th>Number of Paths</th>";
  text += "<th>Number of Groups</th>";
  text += "</tr>";
  let str = "./uploads/";
  fs.readdirSync('uploads/').forEach(file => {
    let x = sharedLib.isValid(path.join('uploads/' + file));
    if(x == 1){
      cnt += 1;
      var stats = fs.statSync(path.join(__dirname+'/uploads/' + file));
      var size = Math.round(stats["size"] / 1024);
      text += "<tr><td> <a href = " + file + " download><img src = "+file+" width=200></a></td>";
      text += "<td> <a href = "+file+" download>"+ file +"</a></td>";
      text += "<td>" + size + "KB</td>";
      x = sharedLib.getNumRects(path.join('uploads/' + file));
      text += "<td> " + x + " </td>";
      x = sharedLib.getNumCircs(path.join('uploads/' + file));
      text += "<td> " + x + " </td>";
      x = sharedLib.getNumPaths(path.join('uploads/' + file));
      text += "<td> " + x + " </td>";
      x = sharedLib.getNumGroups(path.join('uploads/' + file));
      text += "<td> " + x + " </td></tr>";
    }
    //text += "<img src = "+file+"><br>";
  });
  if(cnt == 0){
    text += "<tr><td>No Files</td><td>NA</td><td>NA</td><td>NA</td><td>NA</td><td>NA</td><td>NA</td></tr>";
  }
  text += "</table>";
  res.send({
    foo: text
  });
});

app.get('/view', function(req , res){
  var text = "";
  if(req.query.index != 0){
    let file = req.query.value;
    text = "<img src = "+file+" width=800>";
  }
  
  res.send({
    foo: text
  });
});

app.get('/titlendesc', function(req , res){
  var text = "<td>NA</td><td>NA</td>";
  if(req.query.index != 0){
    let file = req.query.value;
    let x = sharedLib.getTitle(path.join('uploads/' + file));
    text = "<td>" + x + "</td>";
    x = sharedLib.getDesc(path.join('uploads/' + file));
    text += "<td>" + x + "</td>";
  }
  
  res.send({
    foo: text
  });
});

app.get('/components', function(req , res){
  var text = "";
  var text2 = "<option value = \"\" label = \"Select One\"></option>";
  if(req.query.index != 0){
    let file = req.query.value;
    let x = JSON.parse(sharedLib.getAllRects(path.join('uploads/' + file)));
    for(var i = 0; i < x.length; i++){
      var u = x[i].units;
      text += "<tr><td> Rectangle " + (i+1) + "</td>";
      text += "<td>x=" + x[i].x+", y="+x[i].y+"<br>Width:"+ x[i].w+u+", Height:"+x[i].h+u+"</td>";
      text += "<td>" + x[i].numAttr + "</td></tr>";
      text2 += "<option value = \"2" + i +"\">" + "Rectangle " + (i+1);
      text2 += "</option>";
    }
    x = JSON.parse(sharedLib.getAllCircs(path.join('uploads/' + file)));
    for(var i = 0; i < x.length; i++){
      var u = x[i].units;
      text += "<tr><td> Circle " + (i+1) + "</td>";
      text += "<td>x=" + x[i].cx+", y="+x[i].cy+"<br>Radius="+ x[i].r+u+"</td>";
      text += "<td>" + x[i].numAttr + "</td></tr>";
      text2 += "<option value = \"1" + i +"\">" + "Circle " + (i+1);
      text2 += "</option>";
    }
    x = JSON.parse(sharedLib.getAllPaths(path.join('uploads/' + file)));
    for(var i = 0; i < x.length; i++){
      var d = x[i].d;
      text += "<tr><td> Path " + (i+1) + "</td>";
      text += "<td>Path Data = " + d + "</td>";
      text += "<td>" + x[i].numAttr + "</td></tr>";
      text2 += "<option value = \"3" + i +"\">" + "Path " + (i+1);;
      text2 += "</option>";
    }
    x = JSON.parse(sharedLib.getAllGroups(path.join('uploads/' + file)));
    for(var i = 0; i < x.length; i++){
      var d = x[i].children;
      text += "<tr><td> Group " + (i+1) + "</td>";
      text += "<td>" + d + " Child Element(s)</td>";
      text += "<td>" + x[i].numAttr + "</td></tr>";
      text2 += "<option value = \"4" + i +"\">" + "Group " + (i+1);
      text2 += "</option>";
    }
  }
  
  res.send({
    foo: text,
    select: text2
  });
});

app.get('/atts', function(req , res){
  var text = "<b>";
  let file = req.query.valuef;
  let s = req.query.value;
  let x = JSON.parse(sharedLib.getAllAtts(path.join('uploads/' + file), s));
  //console.log("I am out");
  for(var i = 0; i < x.length; i++){
    text += "Name: " + x[i].name + ", Value: " + x[i].value + "<br>";
  }
  if(x.length == 0){
    text += "None</b>";
  }
  else{
    text += "</b>";
  }
  res.send({
    foo: text
  });
});

app.get('/edit', function(req , res){
  //var text = "<b>";
  let file = req.query.valuef;
  let s = req.query.value;
  let x = -1;
  if(req.query.index == 0 || req.query.indexf == 0){
    x = -1;
  }
  else{
    x = sharedLib.editAtts(path.join('uploads/' + file), s, req.query.name, req.query.data);
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/title', function(req , res){
  //var text = "<b>";
  let file = req.query.valuef;
  let x = -1;
  if(req.query.indexf == 0){
    x = -1;
  }
  else{
    x = sharedLib.editTitle(path.join('uploads/' + file), req.query.title);
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/desc', function(req , res){
  //var text = "<b>";
  let file = req.query.valuef;
  let x = -1;
  if(req.query.indexf == 0){
    x = -1;
  }
  else{
    x = sharedLib.editDesc(path.join('uploads/' + file), req.query.desc);
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/rect', function(req , res){
  //var text = "<b>";
  //let f1 = '\\-?\\d*\\.?\\d+';
  //let f2 = '\\d*\\.?\\d+';
  let x = -1;
  let file = req.query.valuef;
  var rx = req.query.x;
  //rx = rx.(f1);
  //console.log(isNaN(req.query.x));
  if( req.query.indexf == 0){
    x = -1;
  }
  else if (isNaN(req.query.x) || isNaN(req.query.y) || isNaN(req.query.w) || isNaN(req.query.h)){
    x = 0;
  }
  else{
    var t = {x: Number(req.query.x), y: Number(req.query.y), w: Number(req.query.w), h: Number(req.query.h), units: req.query.units};
    t = JSON.stringify(t);
    x = sharedLib.addRect(path.join('uploads/' + file), t);
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/circ', function(req , res){
  //var text = "<b>";
  //let f1 = '\\-?\\d*\\.?\\d+';
  //let f2 = '\\d*\\.?\\d+';
  let x = -1;
  let file = req.query.valuef;
  //var rx = req.query.x;
  //rx = rx.(f1);
  //console.log(isNaN(req.query.x));
  if( req.query.indexf == 0){
    x = -1;
  }
  else if (isNaN(req.query.x) || isNaN(req.query.y) || isNaN(req.query.r)){
    x = 0;
  }
  else{
    var t = {cx: Number(req.query.x), cy: Number(req.query.y), r: Number(req.query.r), units: req.query.units};
    t = JSON.stringify(t);
    x = sharedLib.addCirc(path.join('uploads/' + file), t);
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/path', function(req , res){
  //var text = "<b>";
  //let f1 = '\\-?\\d*\\.?\\d+';
  //let f2 = '\\d*\\.?\\d+';
  let x = -1;
  let file = req.query.valuef;
  //var rx = req.query.x;
  //rx = rx.(f1);
  //console.log(isNaN(req.query.x));
  if( req.query.indexf == 0){
    x = -1;
  }
  else{
    let da = req.query.d;
    x = sharedLib.addPath(path.join('uploads/' + file), da) ;
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/scaler', function(req , res){
  //var text = "<b>";
  //let f1 = '\\-?\\d*\\.?\\d+';
  //let f2 = '\\d*\\.?\\d+';
  let x = -1;
  let file = req.query.valuef;
  //var rx = req.query.x;
  //rx = rx.(f1);
  //console.log(isNaN(req.query.x));
  if( req.query.indexf == 0){
    x = -1;
  }
  else if (isNaN(req.query.ratio)){
    x = 0;
  }
  else{
    x = sharedLib.scaleRect(path.join('uploads/' + file), req.query.ratio);
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/scalec', function(req , res){
  //var text = "<b>";
  //let f1 = '\\-?\\d*\\.?\\d+';
  //let f2 = '\\d*\\.?\\d+';
  let x = -1;
  let file = req.query.valuef;
  //var rx = req.query.x;
  //rx = rx.(f1);
  //console.log(isNaN(req.query.x));
  if( req.query.indexf == 0){
    x = -1;
  }
  else if (isNaN(req.query.ratio)){
    x = 0;
  }
  else{
    x = sharedLib.scaleCirc(path.join('uploads/' + file), req.query.ratio);
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});

app.get('/svg', function(req , res){
  //var text = "<b>";
  //let f1 = '\\-?\\d*\\.?\\d+';
  //let f2 = '\\d*\\.?\\d+';
  let x = -1;
  let file = req.query.value;
  //var rx = req.query.x;
  //rx = rx.(f1);
  //console.log(isNaN(req.query.x));
  if( req.query.found != -1){
    x = -1;
  }
  else{
    x = sharedLib.createSvg(path.join('uploads/' + file)) ;
  }
  //console.log("I am out");
  res.send({
    foo: x
  });
});


app.listen(portNum);
console.log('Running app at localhost: ' + portNum);