<?php
/*
Bryan and Mo  
*/

class Event{
    private $id; //event unique id
    private $name; //name of event
    private $desription; // description of event
    private $address; // address of event
    private $state; // state () of event
    private $city;
    private $zip;

    function __construct($f, $n, $d, $a, $s, $c, $z){
        $this->id = $f
        $this->name = $n
        $this->description = $d
        $this->address = $a
        $this->state = $s
        $this->city = $c
        $this->zip = $z


    }

    function get_id() {
            return $this->id;
    }

    function get_name(){
        return $this->name;
    }

    function get_description(){
        return $this->description;
    }

    function get_address(){
        return $this->address;
    }

    function get_state(){
        return $this->state;
    }

    function get_city(){
        return $this->city;
    }
    
    function get_zip(){
        return $this->zip;
    }




}
 
?>






