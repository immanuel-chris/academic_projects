<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
$username = validate($_POST['username']);
$taskid = validate($_POST['taskid']);

//mark as done on taskassocs
$updateSql = mysqli_query($conn, "UPDATE taskassocs SET finished='1' WHERE username='$username' AND taskid='$taskid'");

//get some task info
$sqlTask = "SELECT * FROM tasks WHERE id='$taskid' LIMIT 1";
$resultTask = mysqli_query($conn, $sqlTask);
$rowFromResult = mysqli_fetch_assoc($resultTask);
$organizer = $rowFromResult['organizer'];
$dateC = (new DateTime($rowFromResult['created']))->format('F jS, Y');

//get name of volunteer
$sqlFullName = "SELECT * FROM users WHERE username='$username' LIMIT 1";
$rowName = mysqli_fetch_assoc(mysqli_query($conn, $sqlFullName));
$middleName = !empty($rowName['middlename']) ? " ".$rowName['middlename']." " : " ";
$fullName = "<a href=\"http://".$_SERVER['HTTP_HOST']."/dashboard/?page=profile&profile-id=".$rowName['id']."\">".$rowName['firstname'].$middleName.$rowName['familyname']."</a>";

//send notif to organizer
$notifDesc = $fullName." has finished the task \"".$rowFromResult['taskname']."\" you assigned to them on ".$dateC.". <a href=\"http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks\">See tasks>></a>";
$dateCreated = date('Y-m-d H:i:s');
$sendNotifSQL = "INSERT INTO notification(username, notifdesc, sent) VALUES('$organizer', '$notifDesc', '$dateCreated')";
mysqli_query($conn, $sendNotifSQL);

header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard?page=tasks&success=Task marked successfully");
exit();
?>