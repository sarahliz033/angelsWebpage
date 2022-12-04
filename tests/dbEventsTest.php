<?php
/*
 * Copyright 2013 by Jerrick Hoang, Ivy Xing, Sam Roberts, James Cook, 
 * Johnny Coster, Judy Yang, Jackson Moniaga, Oliver Radwan, 
 * Maxwell Palmer, Nolan McNair, Taylor Talmage, and Allen Tucker. 
 * This program is part of RMH Homebase, which is free software.  It comes with 
 * absolutely no warranty. You can redistribute and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation
 * (see <http://www.gnu.org/licenses/ for more information).
 * 
 */

/*
 * Modified March 2012
 * @Author Taylor and Allen
 */
use PHPUnit\Framework\TestCase;
include_once(dirname(__FILE__).'/../database/dbEvents.php');
include_once(dirname(__FILE__).'/../domain/Event.php');
class dbEventsTest extends TestCase {
      function testdbEvents() {
      	// add two people to the database
        $m = new Event("2","testevent","This is a test","Bosnia","Greater Bosnia","Bosnovia","6969");
		$this->assertTrue(add_event($m));
	/*	
		$m2 = new Person("Fred","Wilson", "portland","14 Boyer Ave", "Portland", "ME", 04503,
		5093456789, "home",5098889999,"cell","alfred@whitman.edu","volunteer","","","active", 
		"McDonalds","manager","","year","a motivation2","First Aid", "",
		"Wed:9-12:portland,Sun:afternoon:portland","","15-02-27:1730-2100:portland:3.5","91-09-25","07-04-14","other","Some notes","");
		$this->assertTrue(add_person($m2));
*/
		// retrieve the person and test the fields
		$p = retrieve_event("2");
		$this->assertTrue($p!==false);
		$this->assertTrue($p->get_name() == "testevent");
		$this->assertTrue($p->get_description() == "This is a test");
		$this->assertEquals($p->get_address() == ("Bosnia"));
		$this->assertEquals($p->get_state() == ("Greater Bosnia"));
		$this->assertTrue($p->get_city() == "Bosnovia");
		$this->assertTrue($p->get_zip() == "6969");
		/*
		$p2 = retrieve_person("Fred5093456789");
		$this->assertTrue($p2!==false);
		$this->assertTrue($p2->get_status() == "active");
		$this->assertTrue($p2->get_email() == "alfred@whitman.edu");
		$this->assertEquals($p2->get_type(), array("volunteer"));
		$this->assertEquals($p2->get_hours(), array("15-02-27:1730-2100:portland:3.5"));
		$this->assertTrue($p2->get_birthday() == "91-09-25");
		*/
		// remove the person
		//$this->assertTrue(remove_event("2")); Removing Event
		//$this->assertTrue(remove_person("Fred5093456789"));
		
		
		echo("testdbEvents complete\n");

      }
}


?>
