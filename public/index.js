// Put all onload AJAX calls here, and event listeners
$(document).ready(function() {
    // On page-load AJAX Example
    
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/list',   //The server endpoint we are connecting to
        data: {
            name1: "Value 1",
            name2: "Value 2"
        },
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
          document.getElementById("svgs").innerHTML = data.foo;
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/log',   //The server endpoint we are connecting to
        data: {
            name1: "Value 1",
            name2: "Value 2"
        },
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
          document.getElementById("log").innerHTML = data.foo;
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
    

    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
  
    $('form#uploadForm').submit(function(e){
        //$('#upload').html("Form has data: "+$('#entryBox').val());
        e.preventDefault();
        var x = document.getElementById("svgs");
        var y = -1;
        var rx = $('#upfile').val();
        //alert("ha2");
        //alert(x);
        for(var i = 0; i < x.options.length; i++){
            if(x.options[i].value == rx){
                y = i;
                break;
            }
        }
        console.log('Active');
        
        if(y != - 1){
           //Pass data to the Ajax call, so it gets passed to the server
            var form = $('#uploadForm')[0];
            var data = new FormData(form);
            $.ajax({
                type: 'POST',
                url: '/upload',
                enctype: 'multipart/form-data',
                data: data,
                async: false,
                processData: false,
                contentType: false,
                cache: false,
                success: function (data) {
                    console.log('Thank God it worked!');
                },
                fail: function(error) {
                    // Non-200 return, do something with error
                    console.log(error); 
                }
            });
            window.location.reload();
        //return false;
        
        }
        else{
            alert("A file with this name already exists");
        }
    }); 
  
    $('#svgs').on('change', function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //Pass data to the Ajax call, so it gets passed to the server
        //alert("Server");
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/view',   //The server endpoint we are connecting to
            data: {
                index: x,
                value: y
            },
            success: function (data) {
            
                document.getElementById("imgpanel").innerHTML = data.foo;
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/titlendesc',   //The server endpoint we are connecting to
            data: {
                index: x,
                value: y
            },
            success: function (data) {
            
                document.getElementById("tnd").innerHTML = data.foo;
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
        
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/components',   //The server endpoint we are connecting to
            data: {
                index: x,
                value: y
            },
            success: function (data) {
                document.getElementById("componentpanel").innerHTML = data.foo;
                document.getElementById("atts").innerHTML = data.select;
                document.getElementById("viewatts").innerHTML = "<b>None</b>";
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    $('#atts').on('change', function(e){
        e.preventDefault();
        //alert("Hi");
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var a = document.getElementById("atts").selectedIndex;
        var b = document.getElementById("atts").options[a].value;
        //alert("Hi2");
        //Pass data to the Ajax call, so it gets passed to the server
        //alert("Server");
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/atts',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                index: a,
                value: b
            },
            success: function (data) {
                //alert("Ehat");
            
                document.getElementById("viewatts").innerHTML = data.foo;
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    $('#attform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var a = document.getElementById("atts").selectedIndex;
        //alert(a);
        var b = document.getElementById("atts").options[a].value;
        var c = $('#entername').val();
        var d = $('#entervalue').val();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/edit',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                index: a,
                value: b,
                name: c,
                data: d
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image and a component");
                }
                else if (data.foo == 0){
                    alert("Invalid Attribute");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    $('#titleform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var c = $('#entertitle').val();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/title',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                title: c
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image");
                }
                else if (data.foo == 0){
                    alert("Invalid Name");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    $('#descform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var c = $('#enterdesc').val();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/desc',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                desc: c
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image");
                }
                else if (data.foo == 0){
                    alert("Invalid Description");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    $('#rectform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var rx = $('#enterx').val();
        var ry = $('#entery').val();
        var rw = $('#enterw').val();
        var rh = $('#enterh').val();
        var ru = $('#enteru').val();
        /*var j = {x: rx,
                y: ry,
                w: rw,
                h: rh,
                units: ru};*/
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/rect',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                x: rx, 
                y: ry, 
                w: rw, 
                h: rh, 
                units: ru
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image");
                }
                else if (data.foo == 0){
                    alert("Invalid Rectangle");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    
    $('#circform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var rx = $('#entercx').val();
        var ry = $('#entercy').val();
        var rw = $('#enterr').val();
        var ru = $('#entercu').val();
        /*var j = {x: rx,
                y: ry,
                w: rw,
                h: rh,
                units: ru};*/
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/circ',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                x: rx, 
                y: ry, 
                r: rw, 
                units: ru
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image");
                }
                else if (data.foo == 0){
                    alert("Invalid Circle");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    
    $('#pathform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var rx = $('#enterd').val();
        /*var j = {x: rx,
                y: ry,
                w: rw,
                h: rh,
                units: ru};*/
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/path',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                d: rx
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image");
                }
                else if (data.foo == 0){
                    alert("Invalid Path");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    
    $('#scalerform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var rx = $('#scaler').val();
        /*var j = {x: rx,
                y: ry,
                w: rw,
                h: rh,
                units: ru};*/
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/scaler',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                ratio: rx
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image");
                }
                else if (data.foo == 0){
                    alert("Invalid Ratio");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    
    $('#scalecform').submit(function(e){
        e.preventDefault();
        var x = document.getElementById("svgs").selectedIndex;
        var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var rx = $('#scalec').val();
        /*var j = {x: rx,
                y: ry,
                w: rw,
                h: rh,
                units: ru};*/
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/scalec',   //The server endpoint we are connecting to
            data: {
                indexf: x,
                valuef: y,
                ratio: rx
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("Choose an image");
                }
                else if (data.foo == 0){
                    alert("Invalid Ratio");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
    
    $('#svgform').submit(function(e){
        e.preventDefault();
        //var x = document.getElementById("svgs").selectedIndex;
        //var y = document.getElementById("svgs").options[x].value;
        //alert("Hi1");
        var rx = $('#svg').val();
        //alert("ha1");
        var x = document.getElementById("svgs");
        var y = -1;
        //alert("ha2");
        //alert(x);
        for(var i = 0; i < x.options.length; i++){
            if(x.options[i].value == rx){
                y = i;
                break;
            }
        }
        //alert("ha3");
        /*var j = {x: rx,
                y: ry,
                w: rw,
                h: rh,
                units: ru};*/
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything 
            url: '/svg',   //The server endpoint we are connecting to
            data: {
                found: y,
                value: rx
            },
            success: function (data) {
                //alert("Ehat");
                if(data.foo == -1){
                    alert("This Name is Already Taken");
                }
                else if (data.foo == 0){
                    alert("Invalid Entry");
                }
                else{
                    alert("It was Successful!!!!")
                    window.location.reload();
                }
                
            //$('#blah').html(data.foo+"' from server");
            //We write the object to the console to show that the request was successful
            //console.log(data); 

            },
            fail: function(error) {
                // Non-200 return, do something with error
                console.log(error); 
            }
        });
    });
});