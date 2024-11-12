# Vacation Rental Price Recommendation System
A stupidly not so simple price recommendation system for vacation rentals in Melaka area. The rule-based inference engine will be generated based on the data that are (read will be) scraped from TripAdvisor. 

## Language: C++

### Update 0.1: 
I try to use object-oriented style as I really love how the file is structured and such. But then once I include MySQL, it become harder to use purely OOP (I admit I'm a bit lazy here to try, as I only follow the example, but hey, if it work, don't break it right). So for now, it's kinda semi-OOP and semi-structed, something like that. Will definitely structed it later (a lie, don't believe me).

As for CRUD, now I can connect with MySQL and do thing that it should do - ie. create, read, update, delete. My database is still quite a mess though so I will update it later. Other than that, I think it is fine for now.

### Update 0.2:
So I can't scrape anything from TripAdvisor as the site use JS to dynamically render content, so I can't just download source and parse. I try to use Selenium and Qt WebEngine, but failed. Hard. I try to look for other alternative but also fail to implement any options. What a noob. 
Anyway, right now, I change my plan to scrape from, ta-da, Google! As you know, Google also list hotel and vacation rental, so I think I gonna scrape from there. 
Additionally, another failure that I faced is that I can't make any HTML parsing library work (and I also consider using libxml to change HTML to XML tree, and parse it, but it seems a lot of work and complex, so no) so, for now, I am just going to use regex to parse the HTML. Hope this work.
Ciao.

### {TO-DO}:
- [ ]  Refactor the code and database. Update database to reflect attribute from Google instead of TripAdvisor
- [ ] Parse the HTML using regex. Should finish it before next week. Please.
- [ ] Analysis of scraped data
