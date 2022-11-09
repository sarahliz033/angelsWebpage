<?php
session_start();
session_cache_expire(45);

?>
<title>Volunteer Feedback</title>

<html>
    <body>
        <form action="index.php" method="post">
            <fieldset style="border: 10px groove">
                <p style="color: red">* required field</p>
                <legend>Volunteer Feedback Form</legend>
                <p>Name: <input type="text" name="name"></p>
                <p>E-mail: <input type="text" name="email"></p>
                <p>Event You Volunteered At: <input type="text" name="eventName"></p>
                <p>Feedback: </p><textarea name="feedback" rows="5" cols="40"></textarea>
                
                <input type="submit">
            </fieldset>
        </form>

    </body>
</html>
