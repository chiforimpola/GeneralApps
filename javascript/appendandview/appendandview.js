

    <script language="javascript">
		
		var afilio = 0;
		var pid = "null";
		var order_id = "null";
		var order_price = "null";
		var protocol = '';
		var action = new Array();
		action['order_id'] = new Date().getTime();
		action['order_price'] = 'null';
		
		for (var i = 0;i < document.images.length;i++)
		{
			var imgurl = document.images[i].src;
			var buffer = "";
			for (var i2 = 0;i2 < imgurl.length;i2++)
			{
				buffer += imgurl[i2];
				if (afilio == 0 && buffer == "https://secure.afilio.com.br")
				{
					afilio = 1;
					protocol = 'https';
				}
				else if (afilio == 0 && buffer == "http://v2.afilio.com.br")
				{
					afilio = 1;
					protocol = 'http';
				}
				else if (afilio == 1)
				{
					if (imgurl[i2] == '?' || imgurl[i2] == '&')
					{
						var i3 = i2+1;
						var parameter = "";
						var value = "";
						while (imgurl[i3] != '=' && i3 < imgurl.length)
						{
							parameter += imgurl[i3]
							i3++;
						}
						i3++;
						while (imgurl[i3] != '&' && i3 < imgurl.length)
						{
							value += imgurl[i3];
							i3++;
						}
						alert(parameter+'='+value);
						if (parameter == 'pid') pid = value;
						else if (parameter == 'order_id') order_id = value;
						else if (parameter == 'order_price') order_price = value;
					}
					
					if (order_id != 'null' && order_price != 'null' && pid != 'null')
					{
						var pixel_afilio = document.createElement ('img');
						var pixel_src = '';
						
						if (action['order_price'] != 'null')
						    order_price = action['order_price'];
						    
						if (action['order_id'] != 'null')
						    order_id = action['order_id'];
						
						if (protocol == 'http')
						    pixel_src = "http://v2.afilio.com.br/sale.php?pid="+pid+"&order_id="+order_id+"&order_price="+order_price;
						else if (protocol == 'https')
						    pixel_src = "https://secure.afilio.com.br/sale.php?pid="+pid+"&order_id="+order_id+"&order_price="+order_price;
						    
						pixel_afilio.setAttribute ('border', '0');
						pixel_afilio.setAttribute ('width', '1');
						pixel_afilio.setAttribute ('heigth', '1');
						pixel_afilio.setAttribute ('src', pixel_src);
						document.body.appendChild (pixel_afilio);
						
						return;
					}
				}
			}
		}
		
	</script>


