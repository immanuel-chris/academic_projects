<?php
$profileId = $_SESSION['id'];
$sqlUserId = "SELECT * FROM users WHERE id='$profileId'";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);
?>

<h1>Hello <?php echo $rowFromIdResult['firstname']; ?>!</h1>

<div class="main-page-box-containers">
<!-- for pending tasks -->
<div class="main-page-left">
<h2>Pending Tasks</h2>
<?php 
    // get tasks assigned to the logged in user
    echo "<table class=\"task-list\">";
    $sqlUserTasks = "SELECT * FROM taskassocs WHERE username='".$rowFromIdResult['username']."' AND finished=0";
    $resultGetAssigneds = mysqli_query($conn, $sqlUserTasks);
    if (mysqli_num_rows($resultGetAssigneds) > 0) {
        while ($row = mysqli_fetch_assoc($resultGetAssigneds)) {
            //get data associated with task
            $sqlTask = "SELECT * FROM tasks WHERE id=".$row['taskid']." LIMIT 1";
            $resultTask = mysqli_query($conn, $sqlTask);
            $rowFromTask = mysqli_fetch_assoc($resultTask);

            //get task organizer name
            $taskOrgzName = "<a href=\"?page=profile&profile-id=".getIdFromUsername($rowFromTask['organizer'], $conn)."\">".getNameFromUsername($rowFromTask['organizer'], $conn)."</a>";

            //turn numeral deadline date to datetime
            if ($rowFromTask['deadline'] != "0000-00-00") {
                $date = new DateTime($rowFromTask['deadline']);
                $dateF = $date->format('F jS, Y');
            }
            else {
                $dateF = "n/a";
            }

            echo "<tr><td>
            <b>Name</b>: ".$rowFromTask['taskname']." (by ".$taskOrgzName.")
            <br />
            <b>Description</b>: ".$rowFromTask['taskdesc']."
            <br />
            <b>Deadline</b>: ".$dateF."
            <br />
            <b>Location</b>: ".$rowFromTask['location']."
            </td></tr>";
        }
    }
    else {
        echo "<tr>
        <td>No tasks so far...</td>
        </tr>";
    }
    echo "</table>";
?>
You may check all available tasks <a href="?page=tasks">here.</a>
</div>
<!-- for news and stuff -->
<div class="main-page-right">
<h2>Current News</h2>
None so far...
</div>
</div>