<?php
session_start();
session_cache_expire(45);

?>
<title>Volunteer Feedback</title>

<html>
    <body>
        <p style="color: red">* required field</p>
        <form action="index.php" method="post">
            Name: <input type="text" name="name"><br>
            E-mail: <input type="text" name="email"><br>
            Event You Volunteered At: <input type="text" name="eventName"><br>
            Feedback: <input type=text" name="feedback"><br>
            
            <input type="submit">
        </form>

    </body>
</html>
