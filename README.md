# Rochdale Village NORC Website

A modern, NORC-only website concept for Rochdale Village.

## Included

- Responsive HTML website
- Modern blue / purple / black visual system
- NORC-only navigation
- About NORC
- Supportive services
- Activities
- Client section
- Client support/request form
- Contact information
- Mobile navigation
- Scroll animations
- Optional C++ HTTP backend

## Run the website without C++

You can simply open `index.html` in a browser.

For best results, use a local web server because the client form uses `/api/client`.

## Run the C++ version

### Linux / macOS

Open a terminal in this folder:

```bash
g++ -std=c++17 -O2 server.cpp -o norc_server
./norc_server
```

Then visit:

http://localhost:8080

### Windows / MinGW

```bash
g++ -std=c++17 -O2 server.cpp -lws2_32 -o norc_server.exe
norc_server.exe
```

Then visit:

http://localhost:8080

Client submissions are saved locally to:

`client_submissions.txt`

## Important before public deployment

This C++ server is intentionally simple and is appropriate for a school/project demonstration or local prototype. A real public deployment should use HTTPS, server-side validation, secure storage/database handling, authentication for staff, CSRF protection, rate limiting, and a production web server.

## Source information used for the site content

The current Rochdale Village NORC office information and program description were checked against the Rochdale Village website. The office is listed at 169-65 137th Avenue, Rooms 19 & 20, with NORC office hours Monday-Friday, 9:00 AM-5:00 PM and phone (718) 525-2800 Ext. 2.

The site intentionally avoids copying the original page's design and instead presents the information as a new NORC-focused interface.


## NORC Team

Clickable staff profile cards were added for Phara Carolei, Irvica Galla, Hurgens Pignard (Mr. P), Sade Afolabi, Utkarsha Pagar, and Deevika Presaud. The bios are concise role-based draft profiles and should be replaced with approved official biographies before public publication.


## Uploaded Branding & Home Photo

- `home-team-photo.png` — uploaded office/team photo used as the Home hero image.
- `rochdale-logo.png` — uploaded Rochdale logo used in the header and browser/app tab icon (favicon).


## Breast Cancer Donation Page
The website now includes `breast-cancer-donation.html`, linked from the main navigation and home page. The page is designed for a breast cancer awareness/support fundraiser and is prepared for Zeffy checkout.

To activate the donation form, create the official Rochdale Village NORC breast cancer campaign in Zeffy, copy its campaign/share URL, and replace `PASTE_YOUR_ZEFFY_BREAST_CANCER_CAMPAIGN_URL_HERE` in `breast-cancer-donation.html`. Do not use another organization's Zeffy campaign URL.


## Breast Cancer Donation
The Breast Cancer Support page is connected to the Zeffy campaign URL supplied for this website:
`https://www.zeffy.com/en-US/donation-form/donate-to-change-lives-of-older-adults`

Donations are processed on Zeffy; the NORC website does not collect card details.


Instagram: https://www.instagram.com/rochdale_village_norc/
