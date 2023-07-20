a=open('demoproject.html','w')
t="""
<html>
    <head>
        <title>test</title>
        <style>
        body{
        margin:0px;
        padding:0px;
        text-decoration:none;
        }
        .header{
        height:50px;
        width:100%;
        background-color:black;
        }
        .phone{
        height:50px;
        width:33.33%;
        background-color:indigo;
        float:left;
        }
        .phone a{
        color:white;
        display:block;
        text-align:center;
        line-height:50px;
        font-size:17px;
        letter-spacing:3px;
        text-decoration:none;
        font-weight:bold;
        }
        .moving-text{
        height:50px;
        width:33.33%;
        background-color:green;
        float:left;
        }
        .moving-text span{
        color:white;
        font-size:24px;
        font-weight:bold;
        font-style:italic;
        line-height:50px;
        }
        .social{
        height:50px;
        width:33.34%;
        background-color:pink;
        float:left;
        }
        .social ul{
        text-align:center;
        }
        .social ul li{
        display:inline-block;
        }
        .social ul li a{
        color:white;
        font-weight:bold;
        background-color:black;
        text-decoration:none;
        padding:3px 5px;
        border-radius:5px;
        }
        </style>
    </head>
    <body bgcolor="red">
    <div class="header">
        <div class="phone">
            <a href="tel:+916295939450">+916295939450</a>
        </div>
        <div class="moving-text">
        <span><marquee>This is moving Text</marquee></span>
        </div>
        <div class="social">
        <ul>
            <li><a href="https:\\www.facebook.com">Facebook</a></li>
            <li><a href="https:\\www.whatsapp.com">whatsapp</a></li>
            <li><a href="https:\\www.twitter.com">twitter</a></li>
            <li><a href="https:\\www.instagram.com">Instagram</a></li>
        </ul>
        </div>
    </div>
    </body>
</html>  
"""
a.write(t)
a.close()