# NoSwap

NoSwap is project for Linux, designed to prevent swapping of specific process. The project consists of two parts: 

* a suid executable to set memory locking limits and a fork the executable
* a preload library that locks desired portion of memory for the newly spawned process

NoSwap is intended to run on resource-depleted machines that are expected to use swap heavily.

## Authors

* **Marek Rost** - [GitHub](https://github.com/marekrost)

See also the list of [contributors](https://github.com/marekrost/noswap/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details

## Author
- Marek Rost
