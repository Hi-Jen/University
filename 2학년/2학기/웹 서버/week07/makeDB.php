<?php
 $conn = mysqli_connect('localhost','root','tv591100');
  if(!$conn) die('Could not connect:'.mysqli_error($conn));

  $sql = "create database week07";
  if(!mysqli_query($conn,$sql)) echo 'Error creating database:' . mysqli_error($conn)."\n";
  else echo 'Database week07 is created'."\n";
  ?>
