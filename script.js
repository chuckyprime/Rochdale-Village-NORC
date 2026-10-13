const menuToggle = document.getElementById("menuToggle");
const navLinks = document.getElementById("navLinks");

menuToggle.addEventListener("click", () => {
  const open = navLinks.classList.toggle("open");
  menuToggle.setAttribute("aria-expanded", open ? "true" : "false");
});

document.querySelectorAll(".nav-links a").forEach(link => {
  link.addEventListener("click", () => {
    navLinks.classList.remove("open");
    menuToggle.setAttribute("aria-expanded", "false");
  });
});

document.getElementById("year").textContent = new Date().getFullYear();

const form = document.getElementById("clientForm");
const status = document.getElementById("formStatus");

form.addEventListener("submit", async (event) => {
  event.preventDefault();
  const data = Object.fromEntries(new FormData(form).entries());
  status.textContent = "Submitting...";

  try {
    const response = await fetch("/api/client", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify(data)
    });

    if (response.ok) {
      status.textContent = "Thank you! Your client request has been received.";
      form.reset();
    } else {
      throw new Error("Server unavailable");
    }
  } catch {
    // The front end still works if the optional C++ server is not running.
    status.textContent = "Thanks! Your interest form is ready. Please contact the NORC office to complete your client inquiry.";
  }
});

const observer = new IntersectionObserver(entries => {
  entries.forEach(entry => {
    if (entry.isIntersecting) entry.target.classList.add("visible");
  });
}, {threshold: .12});

document.querySelectorAll(".service-card,.activity,.form-card").forEach(el => {
  el.style.opacity = "0";
  el.style.transform = "translateY(18px)";
  el.style.transition = "opacity .6s ease, transform .6s ease";
  observer.observe(el);
});

document.addEventListener("DOMContentLoaded", () => {
  document.querySelectorAll(".visible").forEach(el => {
    el.style.opacity = "1";
    el.style.transform = "translateY(0)";
  });
});

const style = document.createElement("style");
style.textContent = ".service-card.visible,.activity.visible,.form-card.visible{opacity:1!important;transform:translateY(0)!important}";
document.head.appendChild(style);

const staffBios={phara:{initials:"PC",name:"Phara Carolei",role:"DIRECTOR",photo:"phara-profile.jpg",bio:"As Executive Director of the Rochdale Village NORC program, Phara Carolei helps guide the team and coordinate services that support older adults in the community. Her role centers on program leadership, community engagement and helping ensure residents can access meaningful NORC resources."},irvica:{initials:"IG",name:"Irvica Galla",role:"REGISTERED NURSE",photo:"irvica-profile.jpg",bio:"Irvica Galla serves as the NORC Registered Nurse, supporting the health and wellness needs of older adults. Her role can include health education, wellness outreach, coordination and helping residents connect with appropriate health resources."},hurgens:{initials:"HP",name:"Hurgens Pignard (Mr. P)",role:"CASE WORKER",photo:"pignard-profile.jpeg",bio:"Hurgens Pignard, known as Mr. P, serves as a Case Worker with the NORC team. His work focuses on listening to residents, helping identify needs and connecting individuals with appropriate services, benefits and community resources."},sade:{initials:"SA",name:"Sade Afolabi",role:"SOCIAL WORKER",photo:"sade-profile.jpg",bio:"Sade Afolabi serves as a Social Worker with the NORC program. Her role focuses on supporting residents through social-service needs, providing guidance and helping strengthen connections between residents and available community resources."},utkarsha:{initials:"UP",name:"Utkarsha Pagar",role:"DATA MANAGEMENT SPECIALIST / ADMIN ASST.",photo:"utkarsha-profile.jpg",bio:"Utkarsha Pagar supports the NORC team through data management and administrative coordination. Her work helps keep program information organized and supports the day-to-day administrative needs of the office and its services."},deevika:{initials:"DP",name:"Deevika Presaud",role:"CASE WORKER",photo:"deevika-profile.jpg",bio:"Deevika Presaud serves as a Case Worker with the NORC team. Her role focuses on resident support, identifying individual needs and helping connect older adults with appropriate services, programs and community resources."}};
const bioModal=document.getElementById("bioModal"),bioClose=document.getElementById("bioClose"),bioName=document.getElementById("bioName"),bioRole=document.getElementById("bioRole"),bioText=document.getElementById("bioText"),bioAvatar=document.getElementById("bioAvatar");
function openBio(key){const m=staffBios[key];if(!m)return;bioName.textContent=m.name;bioRole.textContent=m.role;bioText.textContent=m.bio;bioAvatar.textContent=m.initials;const dialog=bioModal.querySelector(".bio-dialog");dialog.style.backgroundImage=`url("${m.photo}")`;dialog.classList.toggle("sade-bio",key==="sade");bioModal.classList.add("open");bioModal.setAttribute("aria-hidden","false");document.body.style.overflow="hidden";bioClose.focus()}
function closeBio(){bioModal.classList.remove("open");bioModal.setAttribute("aria-hidden","true");document.body.style.overflow=""}
document.querySelectorAll(".staff-card").forEach(c=>c.addEventListener("click",()=>openBio(c.dataset.member)));bioClose.addEventListener("click",closeBio);document.querySelector("[data-close-bio]").addEventListener("click",closeBio);document.addEventListener("keydown",e=>{if(e.key==="Escape"&&bioModal.classList.contains("open"))closeBio()});
