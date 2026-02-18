<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
$id = validate($_POST['id']);
$taskname = validate($_POST['taskname']);
$deadline = validate($_POST['deadline']);
$location = validate($_POST['location']);
$taskdesc = validate($_POST['taskdesc']);

//get task
$sqlTask = "SELECT * FROM tasks WHERE id='$id' LIMIT 1";
$rowTask = mysqli_fetch_assoc(mysqli_query($conn, $sqlTask));

//get organizer name
$organizer = $rowTask['organizer'];
$sqlOFullName = "SELECT * FROM users WHERE username='$organizer' LIMIT 1";
$rowOName = mysqli_fetch_assoc(mysqli_query($conn, $sqlOFullName));
$middleOName = !empty($rowOName['middlename']) ? " ".$rowOName['middlename']." " : " ";
$fullOName = "<a href=\"http://".$_SERVER['HTTP_HOST']."/dashboard/?page=profile&profile-id=".$rowOName['id']."\">".$rowOName['firstname'].$middleOName.$rowOName['familyname']."</a>";

//send notification
$dateCreated = date('Y-m-d H:i:s');
$notifDesc = "The task \"".$rowTask."\" has been edited by ".$fullOName.". <a href=\"http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks\">See Tasks>></a>";

$sqlTaskAssocs = "SELECT * FROM taskassocs WHERE taskid='$id'";
$resultTaskAssocs = mysqli_query($conn, $sqlTaskAssocs);
while ($taskAssoc = mysqli_fetch_assoc($resultTaskAssocs)) {
    mysqli_query($conn, "INSERT INTO notification(username, notifdesc, sent) VALUES('".$taskAssoc['username']."', '$notifDesc', '$dateCreated')");
}

//update tasks
$updateSqlTasks = mysqli_query($conn, "UPDATE tasks SET taskname='$taskname', deadline='$deadline', location='$location', taskdesc='$taskdesc' WHERE id='$id'");

//update taskassocs
$updateSqlTaskAssocs = mysqli_query($conn, "UPDATE taskassocs SET taskname='".$taskname."' WHERE taskid='$id'");

header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=tasks&success=Task edited successfully");
exit();