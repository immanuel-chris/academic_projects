<div id='calendar'></div>

<script src='calendar/calendar.js'></script>
<script>

    document.addEventListener('DOMContentLoaded', function() {
      var calendarEl = document.getElementById('calendar');
      var calendar = new FullCalendar.Calendar(calendarEl, {
        initialView: 'dayGridMonth',
        editable: true, // Allow event adding by dragging and dropping
        eventDrop: function(info) {
          // Event drop handler
          alert('Event ' + info.event.title + ' was dropped on ' + info.event.start.toISOString());
        },
        eventResize: function(info) {
          // Event resize handler
          alert('Event ' + info.event.title + ' was resized to end at ' + info.event.end.toISOString());
        },
        dateClick: function(info) {
          // Date click handler
          var today = new Date();
          var clickedDate = info.date;
          if (clickedDate >= today) {
            var title = prompt('Enter event title:');
            if (title) {
              calendar.addEvent({
                title: title,
                start: clickedDate,
                allDay: true // Full day event
              });
            }
          } else {
            alert('Cannot add events before today.');
          }
        },
        eventClick: function(info) {
          // Event click handler
          if (confirm("Are you sure you want to remove this event?")) {
            info.event.remove(); // Remove the clicked event
          }
        },
        eventRender: function(info) {
          // Event render handler
          var today = new Date();
          if (info.event.start < today) {
            info.event.remove(); // Remove events before today
          }
        }
      });
      calendar.render();
    });

  </script>
