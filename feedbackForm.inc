<?php
/*
 * Copyright 2015 by Allen Tucker. This program is part of RMHC-Homebase, which is free 
 * software.  It comes with absolutely no warranty. You can redistribute and/or 
 * modify it under the terms of the GNU General Public License as published by the 
 * Free Software Foundation (see <http://www.gnu.org/licenses/ for more information).

/*
 * 	personForm.inc
 *  shows a form for a person to be added or edited in the database
 * 	@author Oliver Radwan, Xun Wang and Allen Tucker
 * 	@version 9/1/2008, revised 4/1/2012, revised 3/11/2015
 */

if ($_SESSION['access_level'] >= 0)
    echo '<p><strong>Personnel Edit Form</strong>';
    echo(' Here you can edit your own information in the database.' .
    '<br>When finished, hit <b>Submit</b> at the bottom of this page.');
    echo '<br> (<span style="font-size:x-small;color:FF0000">*</span> denotes required information).';
?>
<form method="POST">
    <input type="hidden" name="old_id" value=<?PHP echo("\"" . $id . "\""); ?>>
    <input type="hidden" name="old_pass" value=<?PHP echo("\"" . $person->get_password() . "\""); ?>>
    <input type="hidden" name="_form_submit" value="1">
    <script>
			$(function(){
				$( "#birthday" ).datepicker({dateFormat: 'y-mm-dd',changeMonth:true,changeYear:true,yearRange: "1920:+nn"});
				$( "#start_date" ).datepicker({dateFormat: 'y-mm-dd',changeMonth:true,changeYear:true,yearRange: "1920:+nn"});
				$( "#screening_status" ).datepicker({dateFormat: 'y-mm-dd',changeMonth:true,changeYear:true,yearRange: "1920:+nn"});
			})
	</script>
    <?PHP 
    	$venues = array('portland'=>"Portland House", 'bangor'=>"Bangor House");       
        echo "<table><tr><td>Where did you volunteer?</td></tr>";
        echo '<tr><td>Date: '. 
	             '</td><td colspan=2><input name="start_date" type="text" id="start_date" value="'.$person->get_start_date().'">';
	   	echo "</td></tr><tr><td>Location<span style='font-size:x-small;color:FF0000'>*</span>: </td>";	
	   	foreach ($venues as $venue=>$venuename) {
	   		echo ('<td><input type="radio" name="location" value="' .$venue.'"'. ($person->get_venue()==$venue?' checked':'').'>');
	    	echo "</td><td>".$venuename."</td>";
	   	}
	   	echo "</tr></table><br>"; 
    ?>
    <fieldset>
        <legend>Personal information:</legend>
    <?php
        if ($person->get_first_name()=="new")
        	echo '<p>First Name<span style="font-size:x-small;color:FF0000">*</span>: <input type="text" name="first_name" tabindex="1">';
        else 
        	echo '<p>First Name: '.$person->get_first_name();
    ?>  &nbsp;&nbsp;&nbsp;&nbsp;  Last Name<span style="font-size:x-small;color:FF0000">*</span>: <input type="text" name="last_name" tabindex="2">
</select>
<?php     
    $phonetypes = array("home", "cell", "work");
    echo '<p>Primary Phone<span style="font-size:x-small;color:FF0000">*</span>: ';
    echo '<input type="text" name="phone1" MAXLENGTH=12 tabindex="7" value="'.'">';
    foreach ($phonetypes as $pvalue)
        echo '<input type="radio" name="phone1type" value="' . $pvalue.'"'.($person->get_phone1type()==$pvalue?' checked':'').'>'.$pvalue.' ';
    echo '<p>Email address: '. '<input type="text" name="email" tabindex="10" value="'.$person->get_email().'">';
    echo '<p>Feedback<span style="font-size:x-small;color:FF0000">*</span>`: '. '<textarea></textarea>';
?>

<script src="lib/jquery-1.9.1.js"></script>
<script src="lib/jquery-ui.js"></script>
</fieldset>

<?php 		  
$types = array('volunteer' => 'House Volunteer', 'weekendmgr' => 'Weekend Manager', 'sub' => 'Flex shift', 'mealprep' => 'Guest Chef', 'events' => 'Events/Special projects', 'manager' => 'Manager');
$descriptions = array('volunteer' => ' -- Assists with the day-to-day operations of the House, such as
				answering phones, assisting families, giving tours, cleaning rooms and common areas, and washing linens.<p>', 
		'weekendmgr' => ' -- Serves as main point of contact during day and overnight hours. Shifts are 
						generally Friday 5pm to Saturday 5pm and/or Saturday 5pm to Sunday noon (Bangor) or 2pm (Portland). Duties include
						preparing rooms for guests, assisting families, responding to emergencies, and coordinating shift volunteers.', 
		'sub' => ' -- available on an as-needed basis to fill in (sub) for an open House Volunteer or Weekend Manager shift.',
		'mealprep' => ' -- Individual or group provides ingredients and prepares evening meal for families (approx. 15-20 people Bangor and 
						20-25 people Portland). Groups should be limited to 6-8 people.', 
		'events' => ' -- Helps with special projects and fundraising events that take place occasionally during the year.', 
		'manager' => ' -- This is a restricted level of Homebase access for House staff and experienced volunteers.');
?>
    <?PHP
    if ($_SESSION['access_level']==2 && $person->get_status() == "applicant") {
        echo "<fieldset>";
        echo "<legend>Applicants only: </legend>";
        if ($_SESSION['access_level'] == 2) {
            $screeningType = $person->get_screening_type();
            $screening = retrieve_dbApplicantScreenings($screeningType);
            $screenings = getall_ApplicantScreenings();
            echo('<p> Screening Type:&nbsp; <select name="screening_type">');
            if ($person->get_screening_type() == "")
                echo('<option value="" SELECTED></option>');
            foreach ($screenings as $s) {
                if ($s->get_status() == "published") {
                    $t = $s->get_type();
                    if ($screeningType == $t) {
                        echo('<option value ="' . $t . '" SELECTED>' . $t . '</option>');
                    } else {
                        echo('<option value ="' . $t . '"> ' . $t . '</option>');
                    }
                }
            }
            echo('</select>&nbsp;');

            // submit button that allows manager to associate person with applicant screening
            //echo(' Hit <input type="submit" value="submit" name="Submit Edits"> to associate '.$person->get_first_name().' with this screening.<br><br>');

            if ($screening) {
                $step_array = $screening->get_steps();
                $date_array = $person->get_screening_status();
                $step_count = count($step_array);
            
            echo("<p><table>");
            echo('<tr><td>Completion Date</td> <td>Step</td></tr>');
            for ($i = 0; $i < $step_count; $i++) {
                $j = $i + 1;
                echo "<tr><td>";
                echo('<tr><td><input type="text" id="screening_status" name="screening_status[]" value="'.$date_array[$i]. '" size="8" /></td>');
                echo('</td><td>' . $j . '. ' . $step_array[$i] . '</td></tr>');
            }
            echo('</table>');
            }
        }    
        echo "</fieldset>";
    }
    
    echo('<input type="hidden" name="schedule" value="' . implode(',', $person->get_schedule()) . '">');
    echo('<input type="hidden" name="hours" value="' . implode(',', $person->get_hours()) . '">');
    echo('<input type="hidden" name="password" value="' . $person->get_password() . ')">');
    echo('<input type="hidden" name="_submit_check" value="1"><p>');
    if ($_SESSION['access_level'] == 0)
        echo('By hitting <input type="submit" value="Submit" name="Submit Edits">, I understand the importance of this volunteer 
                commitment and have answered the application questions honestly and to the best of my knowledge.<br /><br />');
    else
        echo('Hit <input type="submit" value="Submit" name="Submit Edits"> to submit these edits.<br /><br />');
    if ($id != 'new' && $_SESSION['access_level'] >= 2) {
        echo ( 
        'Hit <input type="submit" value="Delete" name="deleteMe"> to delete this entry. <br />' .
        'Hit <input type="submit" value="Reset" name="reset_pass"> to reset this person\'s password.</p>');
    }
    ?>
</form>
