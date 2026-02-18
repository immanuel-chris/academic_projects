<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function validate($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

$taskname = validate($_POST['taskname']);
$usernamesString = validate($_POST['volunteers-input']);
$taskdesc = validate($_POST['taskdesc']);
$userId = validate($_POST['id']);
$deadline = validate($_POST['deadline']);
$location = validate($_POST['location']);

$resultId = mysqli_query($conn, "SELECT * FROM users WHERE id='$userId'");
$rowFromIdResult = mysqli_fetch_assoc($resultId);
$organization = $rowFromIdResult['organization'];
$organizer = $rowFromIdResult['username'];

if (empty($taskname)) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks&error=Task Name cannot be empty");
    exit();
}
else if (empty($usernamesString)) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks&error=Task must have assigned volunteers");
    exit();
}
else if (empty($taskdesc)) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks&error=Task Description cannot be empty");
    exit();
}
else if (empty($location)) {
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks&error=Location cannot be empty");
    exit();
}
else {
    //add task to database
    $dateCreated = date('Y-m-d H:i:s');
    $sqlAddToTasks = "INSERT INTO tasks(taskname, taskdesc, organization, organizer, deadline, location, created) VALUES('$taskname', '$taskdesc', '$organization', '$organizer', '$deadline', '$location', '$dateCreated')";
    $resultAddToTasks = mysqli_query($conn, $sqlAddToTasks);
    $taskId = mysqli_insert_id($conn);

    //get full name of organizer
    $sqlOFullName = "SELECT * FROM users WHERE username='$organizer' LIMIT 1";
    $rowOName = mysqli_fetch_assoc(mysqli_query($conn, $sqlOFullName));
    $middleOName = !empty($rowOName['middlename']) ? " ".$rowOName['middlename']." " : " ";
    $fullOName = "<a href=\"http://".$_SERVER['HTTP_HOST']."/dashboard/?page=profile&profile-id=".$rowOName['id']."\">".$rowOName['firstname'].$middleOName.$rowOName['familyname']."</a>";

    //manage users receiving task
    $pattern = '/\((.*?)\)/';
    $matches = [];
    preg_match_all($pattern, $usernamesString, $matches);
    $usernames = $matches[1];

    foreach($usernames as $username) {
        //add task to taskassocs database
        $sqlAddToTaskAssocs = "INSERT INTO taskassocs(username, taskname, taskid, organization) VALUES('$username', '$taskname', '$taskId', '$organization')";
        mysqli_query($conn, $sqlAddToTaskAssocs);

        //upon receivin task the volunteers receive a notif
        $deadlineR = (new DateTime($deadline))->format('F jS, Y');
        $notifDesc = $fullOName." has assigned to you a new task due ".$deadlineR.". <a href=\"http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks\">See Tasks>></a>";
        $sqlSendNotif = "INSERT INTO notification(username, notifdesc, sent) VALUES('$username', '$notifDesc', '$dateCreated')";
        mysqli_query($conn, $sqlSendNotif);
    }
    
    header("Location: http://".$_SERVER['HTTP_HOST']."/dashboard/?page=tasks&success=Task added successfully");
    exit();
}
?>