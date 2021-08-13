<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** franzudev, ft_containers, twitter_handle, email, project_title, project_description
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/franzudev/ft_containers">
    <img src="logo_size.jpg" alt="Logo" width="480" height="80">
  </a>

<h3 align="center">ft_containers</h3>

  <p align="center">
    Reimplementation of the various container types of the C++ standard
template library. Coded in C++98 standard.
    <br />
    <br />
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project


A 42's cursus project.

We had to reimplement various container types of the STL and provide tests to prove that the containers works like the original ones.
* Vector
* Stack (built on top of Vector)
* Map (built on top of a red-black tree)
* Set (built on top of a red-black tree)

Coded with the C++98 standard.


### Built With

 <a href="https://www.cplusplus.com/">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/1200px-ISO_C%2B%2B_Logo.svg.png" alt="Logo" width="50" height="50">
</a>


<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

Before start make sure to have llvm and build-essentials installed.
* llvm
* build-essentials
* clang++

## Usage

Clone the repo and include the container's header in a .cpp.

Then use the Vector, Stack, Map and Set containers as the ones in the STL. 

Run the run_test.sh to see the difference in performance between our version and the STL version.  


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.






<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/franzudev/ft_containers.svg?style=for-the-badge
[contributors-url]: https://github.com/franzudev/ft_containers/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/franzudev/ft_containers.svg?style=for-the-badge
[forks-url]: https://github.com/franzudev/ft_containers/network/members
[stars-shield]: https://img.shields.io/github/stars/franzudev/ft_containers.svg?style=for-the-badge
[stars-url]: https://github.com/franzudev/ft_containers/network/members
[issues-shield]: https://img.shields.io/github/issues/franzudev/ft_containers.svg?style=for-the-badge
[issues-url]: https://github.com/franzudev/ft_containers/issues
[license-shield]: https://img.shields.io/github/license/franzudev/ft_containers.svg?style=for-the-badge
[license-url]: https://github.com/franzudev/ft_containers/blob/main/LICENSE.md
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://it.linkedin.com/in/federico-fran%C3%A7ois
