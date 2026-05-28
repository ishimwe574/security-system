<!DOCTYPE html>
<html>
<head>
  <title>Dashboard</title>
</head>
<body>

<h1>Security Dashboard</h1>

<button onclick="logout()">Logout</button>

<hr>

<h3>Status Panel</h3>
<p>System: <b id="status">SAFE</b></p>
<p>Sensor: Waiting for data...</p>

<h3>Controls</h3>
<button onclick="alert('Alarm ON')">Alarm ON</button>
<button onclick="alert('Relay ON')">Relay ON</button>

<script>
if (localStorage.getItem("auth") !== "1") {
  window.location.href = "login.html";
}

function logout() {
  localStorage.removeItem("auth");
  window.location.href = "login.html";
}
</script>

</body>
</html>