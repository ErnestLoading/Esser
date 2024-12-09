document.addEventListener("DOMContentLoaded", function () {
    const duomenysMygtukas = document.getElementById("gauti-duomenis");
    const rezultatasDiv = document.getElementById("rezultatas");
  
    duomenysMygtukas.addEventListener("click", () => {
      fetch("http://192.168.1.100/duomenys") // ESP32 IP adresas
        .then((response) => {
          if (!response.ok) {
            throw new Error("Tinklo klaida");
          }
          return response.json();
        })
        .then((data) => {
          rezultatasDiv.textContent = `Požymis 1: ${data.pozymis1}, Požymis 2: ${data.pozymis2}`;
        })
        .catch((error) => {
          console.error("Klaida gaunant duomenis:", error);
        });
    });
  });
  