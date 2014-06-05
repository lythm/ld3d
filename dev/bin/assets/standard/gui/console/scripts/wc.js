
function Console(canvas_id) {

    this.canvas_id = canvas_id;
	this.prompt = "# ";
	this.bgcolor="rgb(0,0,0)";
	this.fontcolor="rgb(255,255,255)";
    this.lines = [];
	this.input_buffer = "";
	this.show_cursor = true;
	this.cmd_history=[];
	this.index_history = 0;
	// resize
	this.resize = function (w, h) {

		var s = document.getElementById(this.canvas_id);

		s.width = w;
		s.height = h;

		this.draw();
	}

	// draw
    this.draw = function () {

		this.clear();

		var s = document.getElementById(this.canvas_id);

		var ctx = s.getContext("2d");

		ctx.fillStyle=this.fontcolor;
		
		for(var i = this.lines.length - 1; i >= 0; --i)
		{
			var x = 5;
			var y =  s.height - (this.lines.length - i ) * 12 - 10;
			if( y <= 0)
			{
				break;
			}
			ctx.fillText(this.lines[i], 10, y);
		}
		
		if(this.show_cursor)
		{
			ctx.fillText(this.prompt + this.input_buffer + "_", 10, s.height - 10);
		}
		else
		{
			ctx.fillText(this.prompt + this.input_buffer, 10, s.height - 10);
		}
	}


	// clear
    this.clear = function () {

		var s = document.getElementById(this.canvas_id);

		var ctx = s.getContext("2d");

		if(this.bgcolor)
		{
			ctx.fillStyle = this.bgcolor;
		}
		else
		{
			ctx.fillStyle = "rgb(0,0,0)";
		}
		ctx.clearRect(0, 0, s.width, s.height);
		ctx.fillRect(0, 0, s.width, s.height);

	}

	// writeln
    this.writeln = function (text) {
		this.lines.push(text);
		this.draw();
	}
	

	// on_key
	this.on_key = function (event){
		var e = event || window.event;
		
		var ch = String.fromCharCode(e.keyCode);

		

		if(e.type == "keydown")
		{
			switch(e.keyCode)
			{
				// up arrow
				case 38:

					if(this.cmd_history.length == 0)
					{
						break;
					}
					
					this.index_history -= 1;
					if(this.index_history < 0)
					{
						this.index_history = 0;
					}
					
					this.input_buffer = this.cmd_history[this.index_history];

					break;
				// down arrow
				case 40:
					if(this.cmd_history.length == 0)
					{
						break;
					}
					
					this.index_history += 1;
					if(this.index_history >= this.cmd_history.length)
					{
						this.index_history = this.cmd_history.length - 1;
						break;
					}

					this.input_buffer = this.cmd_history[this.index_history];
					break;

				// backspace
				case 8:
					
					this.input_buffer = this.input_buffer.slice(0, -1);
					
					e.preventDefault();
					e.stopPropagation()
					//e.returnValue = false;
					//e.cancelBubble = true;
					this.draw();
					return false;
				default:
					return true;
			}
		}

		if(e.type == "keypress")
		{
			switch(e.keyCode)
			{
				// enter
				case 0xd:
					
					this.writeln(this.prompt + this.input_buffer);

					this.parse_cmdln(this.input_buffer);

					if(this.input_buffer.length != 0)
					{
						this.cmd_history.push(this.input_buffer);
						
						if(this.index_history != this.cmd_history.length && this.input_buffer == this.cmd_history[this.index_history])
						{
							this.cmd_history = this.cmd_history.slice(0, this.index_history + 1);
						}

						this.index_history = this.cmd_history.length;
					}
					this.input_buffer = "";
					break;
				
				// `
				case 96:
					break;
				default:
					this.input_buffer += ch;
					break;
			}
		}

		this.draw();

		return true;
	}

	// parse command line
	this.parse_cmdln = function (cmdln){
		var ret = cmdln.split(" ", 1);

		if(ret == "")
		{
			return;
		}
		
		var call = JSON.stringify({call:'on_console_command', parameter:cmdln});
		
		window.invoke_host_call(call);
	}

	// on timer
	this.on_interval = function(){
		this.show_cursor = !this.show_cursor;
		this.draw();
	}

	
	
	setInterval(this.on_interval.bind(this), 500);

}




