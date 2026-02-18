<?php
$profileId = $_SESSION['id'];
$sqlUserId = "SELECT * FROM users WHERE id='$profileId'";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);
?>

<?php if (isset($_GET['error'])) { ?>
    <p class="error"><?php echo $_GET['error']; ?></p>
<?php } else if (isset($_GET['success'])) { ?>
    <p class="success"><?php echo $_GET['success']; ?></p>
<?php } ?>

<?php
//for creating tasks
if ($rowFromIdResult['role'] == 'coordinator') {
?>
<h2>Assign a Task</h2>
<form class="make-task" action="tasks/add_new_task.php" method="post">
    <!--hidden id input-->
    <input type="hidden" name="id" value="<?php echo $rowFromIdResult['id']; ?>">

    <!-- task name -->
    <label>Task Name</label>
    <br />
    <input type="text" name="taskname">
    <br />
    <br />

    <!-- deadline -->
    <label>Deadline</label>
    <br />
    <input type="date" name="deadline" id="deadlineInp">
    <br />
    <br />

    <!-- assigned volunteers -->
    <label>Assigned Volunteers</label>
    <div id="selected-volunteers"></div>
    <input type="hidden" name="volunteers-input" id="volunteers-input" value=""> <!--where data is actually bein added to-->
    <input name="volunteers" list="volunteers-values" id="data-input" placeholder="Search for volunteers..."> <!--where user adds stuff-->
    <datalist id="volunteers-values">
    <?php
        $organization = $rowFromIdResult['organization'];
        $sqlValidMems = "SELECT * FROM users WHERE organization='$organization' AND role='volunteer'";
        $resultValidMems = mysqli_query($conn, $sqlValidMems);
        while ($rowValidMems = mysqli_fetch_assoc($resultValidMems)) {
            $middlename = empty($rowValidMems['middlename']) ? ' ' : ' '.$rowValidMems['middlename'].' ';
            $fullName = $rowValidMems['firstname'].$middlename.$rowValidMems['familyname'];
            $username = $rowValidMems['username'];
            echo '<option value="'.$fullName.' ('.$username.')">';
        }
    ?>
    </datalist>
    <br />
    <br />

    <!-- location -->
    <label>Location</label>
    <input type="text" name="location">

    <!-- description -->
    <label>Description</label>
    <textarea id="bioFormInput" name="taskdesc" maxlength="2048"></textarea>

    <div class="blank-space"></div>

    <button type="submit">Create</button>
</form>

<h2>All Tasks</h2>
<?php
// Get tasks
$resultAllTasks = mysqli_query($conn, "SELECT * FROM tasks");

// Check if the query successfully executed
if ($resultAllTasks) {
    // Check if there are any tasks returned
    if (mysqli_num_rows($resultAllTasks) > 0) {
        echo "<table class=\"task-list\">";

        // If user is organizer, add table header cells
        if ($rowFromIdResult['role'] == 'coordinator') {
            echo "<tr>
            <th>Details</th>
            <th colspan=\"2\">Options</th>
            </tr>";
        }

        // Iterate over each task
        while ($tasks = mysqli_fetch_assoc($resultAllTasks)) {
            //get full name of the organizer
            $sqlGetOrgzName = "SELECT * FROM users WHERE username='".$tasks['organizer']."' LIMIT 1";
            $resultGetOrgzName = mysqli_query($conn, $sqlGetOrgzName);
            $rowGetOrgzName = mysqli_fetch_assoc($resultGetOrgzName);
            $orgzMName = !empty($rowGetOrgzName['middlename']) ? ' '.$rowGetOrgzName['middlename'].' ' : ' ';
            $orgzName = $rowGetOrgzName['firstname'].$orgzMName.$rowGetOrgzName['familyname'];

            //get assigned volunteers
            $sqlGetAssigneds = "SELECT * FROM taskassocs WHERE taskid='".$tasks['id']."'";
            $resultGetAssigneds = mysqli_query($conn, $sqlGetAssigneds);
            $assignedsString = "";

            //create string of list of names
            $assignedsArray = [];
            while ($volunteers = mysqli_fetch_assoc($resultGetAssigneds)) {
                $sqlGetName = "SELECT * FROM users WHERE username='".$volunteers['username']."' LIMIT 1";
                $resultGetName = mysqli_query($conn, $sqlGetName);
                $rowGetName = mysqli_fetch_assoc($resultGetName);
                $volMiddleName = !empty($rowGetName['middlename']) ? ' '.$rowGetName['middlename'].' ' : ' ';
                $volName = "<a href=\"?page=profile&profile-id=".$rowGetName['id']."\">".$rowGetName['firstname'].$volMiddleName.$rowGetName['familyname']."</a>";
                
                //if volunteer is finished with task their name becomes crossed
                if ($volunteers['finished']) {
                    $volName = "<s>".$volName."</s> (finished)";
                }

                $assignedsArray[] = $volName;
            }
            $assignedsString = implode(", ", $assignedsArray);

            //turn numeral deadline date to datetime
            if ($tasks['deadline'] != "0000-00-00") {
                $date = new DateTime($tasks['deadline']);
                $dateF = $date->format('F jS, Y');
            }
            else {
                $dateF = "n/a";
            }
            
            //turn numeral date created to datetime
            $dateC = (new DateTime($tasks['created']))->format('F jS, Y');

            //create table cells
            echo "<tr>
            <td class=\"info-tab\">
            <b>Name</b>: ".$tasks['taskname']." (by  <a href=\"?page=profile&profile-id=".$rowGetOrgzName['id']."\">".$orgzName."</a>)
            <br />
            <b>Description</b>: ".$tasks['taskdesc']."
            <br />
            <b>Created</b>: ".$dateC."
            <br />
            <b>Deadline</b>: ".$dateF."
            <br />
            <b>Location</b>: ".$tasks['location']."
            <br />
            <b>Assigned Volunteers</b>: ".$assignedsString."
            </td>
            <td class=\"delete-task\">
            <button onclick=\"confirmDelete(".$tasks['id'].")\">Delete</button>
            </td>
            <td class=\"edit-task\">
            <button onclick=\"editTask(".$tasks['id'].", '".$tasks['taskname']."', '".$tasks['taskdesc']."', '".$tasks['location']."', '".$tasks['deadline']."')\">Edit</button>
            </td>
            </tr>";
        }
        echo "</table>";
    } 
    else {
        echo "No tasks so far...";
    }
} 
else {
    echo "Error executing query.";
}
?>


<?php
}
else if ($rowFromIdResult['role'] == 'volunteer') {
?>
<h2>Currently Assigned Tasks</h2>
<?php
$username = $rowFromIdResult['username'];
$sqlAssTasks = "SELECT * FROM taskassocs WHERE username='$username'";
$resultValidTasks = mysqli_query($conn, $sqlAssTasks);

// Initially assume no unfinished tasks are found
$unfinishedTasksFound = false;

// Check if there are any rows returned
if (mysqli_num_rows($resultValidTasks) > 0) {
    while ($tasks = mysqli_fetch_assoc($resultValidTasks)) {
        // Check if the task is not finished
        if (!$tasks['finished']) {
            $unfinishedTasksFound = true; // An unfinished task is found
            break; // No need to continue checking once an unfinished task is found
        }
    }

    // If an unfinished task is found, fetch and display all unfinished tasks
    if ($unfinishedTasksFound) {
        // Seek to the beginning of the result set to iterate over it again
        mysqli_data_seek($resultValidTasks, 0);

        echo "<table class=\"task-list\">";
        while ($tasks = mysqli_fetch_assoc($resultValidTasks)) {
            // Only proceed if the task is not finished
            if (!$tasks['finished']) {
                // Similar task fetching and display logic as before
                $sqlGetTask = "SELECT * FROM tasks WHERE id='".$tasks['taskid']."' LIMIT 1";
                $resultGetTask = mysqli_query($conn, $sqlGetTask);
                $specTask = mysqli_fetch_assoc($resultGetTask);

                // Get full name of the organizer
                $sqlGetOrgzName = "SELECT * FROM users WHERE username='".$specTask['organizer']."' LIMIT 1";
                $resultGetOrgzName = mysqli_query($conn, $sqlGetOrgzName);
                $rowGetOrgzName = mysqli_fetch_assoc($resultGetOrgzName);
                $orgzMName = !empty($rowGetOrgzName['middlename']) ? ' '.$rowGetOrgzName['middlename'].' ' : ' ';
                $orgzName = $rowGetOrgzName['firstname'].$orgzMName.$rowGetOrgzName['familyname'];

                // Turn numeral date to datetime
                $dateF = "";
                if ($specTask['deadline'] != "0000-00-00") {
                    $date = new DateTime($specTask['deadline']);
                    $dateF = $date->format('F jS, Y');
                } 
                else {
                    $dateF = "n/a";
                }

                //turn numeral date created to datetime
                $dateC = (new DateTime($specTask['created']))->format('F jS, Y');

                //for changin color of cell
                $cellType = "";
                $checkboxType = "";
                if ($specTask['deadline'] != "0000-00-00") {
                    if (new DateTime($specTask['deadline']) <= new DateTime()) {
                        $cellType = "info-tab-overdue";
                        $checkboxType = "checkbox-overdue";
                    }
                    else {
                        $cellType = "info-tab";
                        $checkboxType = "checkbox";
                    }
                }
                else {
                    $cellType = "info-tab";
                    $checkboxType = "checkbox";
                }

                //make table
                if (!$tasks['finished']) {
                    echo "<tr>
                    <td class=\"".$cellType."\">
                    <b>Name</b>: ".$specTask['taskname']." (by <a href=\"?page=profile&profile-id=".$rowGetOrgzName['id']."\">".$orgzName."</a>)
                    <br />
                    <b>Description</b>: ".$specTask['taskdesc']."
                    <br />
                    <b>Created</b>: ".$dateC."
                    <br />
                    <b>Deadline</b>: ".$dateF."
                    <br />
                    <b>Location</b>: ".$specTask['location']."
                    </td>
                    <td class=\"".$checkboxType."\">
                    
                    <button onclick=\"confirmFinish(".$specTask['id'].")\">Done</button>

                    </td>
                    </tr>";
                }
            }
        }
        echo "</table>";
    } 
    else {
        echo "No assigned tasks yet!";
    }
} 
else {
    echo "No assigned tasks yet!";
}
?>


<h2>Finished Tasks</h2>
<?php
$username = $rowFromIdResult['username'];
$sqlAssTasks = "SELECT * FROM taskassocs WHERE username='$username'";
$resultValidTasks = mysqli_query($conn, $sqlAssTasks);

//initially assume no finished tasks are found
$finishedTasksFound = false;

// Check if there are any rows returned
if (mysqli_num_rows($resultValidTasks) > 0) {
    while ($tasks = mysqli_fetch_assoc($resultValidTasks)) {
        //check if the task is not finished
        if ($tasks['finished']) {
            $finishedTasksFound = true;
            break;
        }
    }

    //if unfinished task is found, fetch and display all unfinished tasks
    if ($finishedTasksFound) {
        mysqli_data_seek($resultValidTasks, 0);
        echo "<table class=\"task-list\">";
        while ($tasks = mysqli_fetch_assoc($resultValidTasks)) {
            //only proceed if task is not finished
            if ($tasks['finished']) {
                $sqlGetTask = "SELECT * FROM tasks WHERE id='".$tasks['taskid']."' LIMIT 1";
                $resultGetTask = mysqli_query($conn, $sqlGetTask);
                $specTask = mysqli_fetch_assoc($resultGetTask);

                //get full name of the organizer
                $sqlGetOrgzName = "SELECT * FROM users WHERE username='".$specTask['organizer']."' LIMIT 1";
                $resultGetOrgzName = mysqli_query($conn, $sqlGetOrgzName);
                $rowGetOrgzName = mysqli_fetch_assoc($resultGetOrgzName);
                $orgzName = getNameFromUsername($rowGetOrgzName['username'], $conn);

                // turn numeral date to datetime
                $dateF = "";
                if ($specTask['deadline'] != "0000-00-00") {
                    $date = new DateTime($specTask['deadline']);
                    $dateF = $date->format('F jS, Y');
                } 
                else {
                    $dateF = "n/a";
                }

                echo "<tr>
                <td class=\"info-tab\">
                <b>Name</b>: ".$specTask['taskname']." (by ".$orgzName.")
                <br />
                <b>Description</b>: ".$specTask['taskdesc']."
                <br />
                <b>Deadline</b>: ".$dateF."
                <br />
                <b>Location</b>: ".$specTask['location']."
                </td>
                <td class=\"checkbox\">
                <button onclick=\"confirmReopen(".$specTask['id'].")\">Re-open</button>
                </td>
                </tr>";
            }
        }
        echo "</table>";
    } 
    else {
        echo "No finished tasks yet!";
    }
} 
else {
    echo "No finished tasks yet!";
}
?>

<?php
}
?>

<script>
//for managing the list of volunteers that can be added
document.getElementById('data-input').addEventListener('input', function(e) {
    const inputVal = e.target.value.trim();

    const isOption = document.querySelector("#volunteers-values option[value='" + inputVal + "']");
    if (inputVal && isOption) {
        const itemList = document.getElementById('selected-volunteers');
        const newItem = document.createElement('div');
        newItem.classList.add('selected-volunteer');
        const textSpan = document.createElement('span');
        textSpan.textContent = inputVal;

        const removeMark = document.createElement('span');
        removeMark.textContent = ' ×';
        removeMark.style.cursor = 'pointer';
        removeMark.onclick = function() {
            const option = document.createElement('option');
            option.value = textSpan.textContent;
            document.getElementById('volunteers-values').appendChild(option);
            newItem.remove();
            updateVolunteersInput();
        };

        newItem.appendChild(textSpan);
        newItem.appendChild(removeMark);
        itemList.appendChild(newItem);
        isOption.remove();
        e.target.value = '';
        updateVolunteersInput();
    }
});

//make deadline input only accept dates after current system date
document.addEventListener("DOMContentLoaded", function() {
    var today = new Date().toISOString().split('T')[0];
    document.getElementById("deadlineInp").setAttribute('min', today);
});

//updatin volunteers input
function updateVolunteersInput() {
    const selectedItems = document.querySelectorAll('#selected-volunteers .selected-volunteer span:first-child');
    const volunteersArray = Array.from(selectedItems).map(item => item.textContent);
    document.getElementById('volunteers-input').value = volunteersArray.join(', ');
}

//variables for popup
function confirmFinish(idInput) {
    showPopup(`Are you sure you're finished with this task?
    <div class="blank-space"></div>
    <form action="tasks/mark_task_done.php" method="post">
        <input type="hidden" name="username" value=<?php echo $rowFromIdResult['username']; ?>>
        <input type="hidden" name="taskid" value=`+idInput+`>
        <div class="popup-button-container">
            <button type="submit">Yes</button>
            <button type="button" onclick="closeButton()">No</button>
        </div>
    </form>`);
}

function confirmReopen(idInput) {
    showPopup(`Are you sure you want to reopen this task?
    <div class="blank-space"></div>
    <form action="tasks/unmark_task_done.php" method="post">
        <input type="hidden" name="username" value=<?php echo $rowFromIdResult['username']; ?>>
        <input type="hidden" name="taskid" value=`+idInput+`>
        <div class="popup-button-container">
            <button type="submit">Yes</button>
            <button type="button" onclick="closeButton()">No</button>
        </div>
    </form>`);
}

function confirmDelete(idInput) {
    showPopup(`Are you sure you want to delete this task? This is irreversible!
    <div class="blank-space"></div>
    <form action="tasks/delete_task.php" method="post">
        <input type="hidden" name="taskid" value=`+idInput+`>
        <div class="popup-button-container">
            <button type="submit" class="popup-button">Yes</button>
            <button type="button"  class="popup-button" onclick="closeButton()">No</button>
        </div>
    </form>`);
}

function editTask(idInput, taskname, taskdesc, location, deadline) {
    showPopup(`<form action="tasks/edit_task.php" method="post" class="make-task">
        <input type="hidden" name="id" value=`+idInput+`>

        <label>Edit Name</label>
        <br />
        <input type="text" name="taskname" value="`+taskname+`"></input>
        <br />
        <br />

        <label>Deadline</label>
        <br />
        <input type="date" name="deadline" id="deadlineInp" value="`+deadline+`">
        <br />
        <br />

        <label>Location</label>
        <br />
        <input type="text" name="location" value="`+location+`">
        <br />
        <br />

        <label>Description</label>
        <textarea id="bioFormInput" name="taskdesc" maxlength="2048">`+taskdesc+`</textarea>

        <div class="blank-space"></div>
        
        <div class="popup-button-container">
            <button type="submit" class="popup-button">Confirm</button>
            <button type="button" class="popup-button" onclick="closeButton()">Cancel</button>
        </div>
    </form>`);
}
</script>